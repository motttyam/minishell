/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktsukamo <ktsukamo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 16:33:23 by ktsukamo          #+#    #+#             */
/*   Updated: 2024/08/10 15:13:37 by ktsukamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	interpret(char **argv, t_var **list, t_tool *tool, t_parser *parser)
{
	pid_t	pid;

	if (exec_builtin(argv, list, tool, parser->count) != -1)
		return ;
	ignore_signal_handler();
	pid = fork();
	if (pid < 0)
		fatal_error("fork");
	else if (pid == 0)
		do_child_process(argv, list, tool, parser->fd);
	else
	{
		close(STDIN_FILENO);
		waitpid(pid, &tool->status, 0);
	}
}

void	do_child_process(char **argv, t_var **list, t_tool *tool, t_fd saved_fd)
{
	char	**env;
	char	*tmp;

	signal(SIGINT, handle_interactive);
	if ((argv[0][0] == '~' && argv[0][1] == '\0') || (argv[0][0] == '~'
			&& argv[0][1] == '/'))
	{
		tmp = *(argv);
		*(argv) = ft_strjoin(tool->home, *argv + 1);
		free(tmp);
	}
	do_path_command(argv, list, tool, saved_fd);
	if (argv[0][0] == '\0')
	{
		put_error_message(argv[0], "command not found", tool);
		exit(127);
	}
	validate_path(argv, list, tool);
	argv[0] = search_path(argv[0], list);
	env = list_to_environ(list);
	execve(argv[0], argv, env);
	free_argv(env);
	put_error_message(argv[0], "command not found", tool);
	exit(127);
}

void	do_path_command(char **argv, t_var **list, t_tool *tool, t_fd saved_fd)
{
	char	**env;

	if (ft_strchr(argv[0], '/'))
	{
		if (access(argv[0], X_OK) == -1)
		{
			put_error_message(argv[0], NULL, tool);
			exit(126);
		}
		else
		{
			env = list_to_environ(list);
			execve(argv[0], argv, env);
			free_argv(env);
			read_file(argv[0], tool, saved_fd, list);
			exit(0);
		}
	}
}

char	*search_path(const char *line, t_var **list)
{
	char	path[PATH_MAX];
	char	*value;
	char	*end;
	char	*dup;

	value = ft_getenv(list, "PATH");
	while (*value)
	{
		ft_bzero(path, PATH_MAX);
		end = ft_strchr(value, ':');
		if (end)
			ft_strlcpy(path, value, end - value + 1);
		else
			ft_bzero(path, PATH_MAX);
		ft_strlcat(path, "/", PATH_MAX);
		ft_strlcat(path, line, PATH_MAX);
		if (access(path, X_OK) == 0)
			return (dup_and_put_error(&dup, path), dup);
		if (end == NULL)
			return ((char *)line);
		value = end + 1;
	}
	return ((char *)line);
}

void	read_file(char *file, t_tool *tool, t_fd saved_fd, t_var **list)
{
	char	buf[PATH_MAX];
	int		fd;
	int		bytes;

	fd = open(file, O_RDONLY);
	if (fd == -1 && errno == EISDIR)
	{
		put_error_message(file, NULL, tool);
		exit(126);
	}
	bytes = read(fd, buf, PATH_MAX);
	if (bytes == -1)
	{
		put_error_message(file, NULL, tool);
		close(fd);
		exit(126);
	}
	buf[bytes] = '\0';
	tool->filename = file;
	lex_and_parse(buf, tool, saved_fd, list);
	close(fd);
}
