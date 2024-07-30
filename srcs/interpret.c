/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyoshimi <nyoshimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 16:33:23 by ktsukamo          #+#    #+#             */
/*   Updated: 2024/07/31 02:58:01 by nyoshimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_stdin_stat(int saved_fd);

char	**list_to_environ(t_var **list)
{
	t_var	*head;
	int		i;
	char	**env;
	char	**top;
	char	*tmp;

	if (!list || !*list)
		return (NULL);
	i = 0;
	head = *list;
	while (head)
	{
		if (head->value != NULL)
			i++;
		head = head->next;
	}
	env = (char **)malloc(sizeof(char *) * (i + 1));
	if (!env)
		handle_malloc_error();
	top = env;
	head = *list;
	while (head)
	{
		if (head->value != NULL)
		{
			*env = ft_strjoin(head->key, "=");
			tmp = *env;
			*env = ft_strjoin(*env, head->value);
			free(tmp);
			env++;
		}
		head = head->next;
	}
	*env = NULL;
	return (top);
}

char	*search_path(const char *line)
{
	char	path[PATH_MAX];
	char	*value;
	char	*end;
	char	*dup;

	value = getenv("PATH");
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
		{
			dup = ft_strdup(path);
			if (dup == NULL)
				fatal_error("strdup");
			return (dup);
		}
		if (end == NULL)
		{
			return ((char *)line);
		}
		value = end + 1;
	}
	return ((char *)line);
}

int	exec_builtin(char **argv, t_var **list, t_tool *tool, int pipeflg)
{
	if (ft_strncmp(argv[0], "echo", 5) == 0)
	{
		exec_echo(argv);
		return (0);
	}
	else if (ft_strncmp(argv[0], "cd", 3) == 0)
	{
		if (!pipeflg)	
			exec_cd(argv, list, tool);
		return (0);
	}
	else if (ft_strncmp(argv[0], "pwd", 4) == 0)
	{
		exec_pwd(list, tool->pwd);
		return (0);
	}
	else if (ft_strncmp(argv[0], "export", 7) == 0)
	{
		exec_export(list, argv,pipeflg);
		return (0);
	}
	else if (ft_strncmp(argv[0], "unset", 6) == 0)
	{
		if (!pipeflg)
			exec_unset(argv, list);
		return (0);
	}
	else if (ft_strncmp(argv[0], "env", 4) == 0)
	{
		exec_env(argv, list);
		return (0);
	}
	else if (ft_strncmp(argv[0], "exit", 5) == 0)
	{
		if (!pipeflg)
			exec_exit(argv, &(tool->status));
		return (0);
	}
	return (-1);
}

void	interpret(char **argv, t_var **list, t_tool *tool,t_fd fd)
{
	pid_t	pid;
	
	if (exec_builtin(argv, list, tool,check_stdin_stat(fd.saved_stdin)) != -1)
		return ;
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid < 0)
		fatal_error("fork");
	else if (pid == 0)
		do_child_process(argv, list);
	else
	{
		close(STDIN_FILENO);
		waitpid(pid,&tool->status,0);
	}
}

void	do_child_process(char **argv, t_var **list)
{
	signal(SIGINT, handle_signal);
	if (ft_strchr(argv[0], '/'))
	{
		if (access(argv[0], X_OK) == -1)
		{
			put_error_message(argv[0], NULL);
			exit(126);
		}
		else
			execve(argv[0], argv, list_to_environ(list));
	}
	else
	{
		argv[0] = search_path(argv[0]);
		execve(argv[0], argv, list_to_environ(list));
		put_error_message(argv[0], "command not found");
		exit(127);
	}
}

int	check_stdin_stat(int saved_fd)
{
	struct stat stdin_stat;
	struct stat saved_stat;
	
	if (fstat(STDIN_FILENO, &stdin_stat) == -1)	
		fatal_error("fstat");
	if (fstat(saved_fd, &saved_stat) == -1)	
		fatal_error("fstat");
	if (stdin_stat.st_dev != saved_stat.st_dev 
	|| stdin_stat.st_ino != saved_stat.st_ino)
		return (1);
	return (0);
}

void	wait_for_all_process(int count)
{
	int i;

	i = 0;
	while (i < count)
	{
		waitpid(-1, NULL, 0);
		i++;
	}
	setup_signal_handler();
}