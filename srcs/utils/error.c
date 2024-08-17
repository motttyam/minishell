/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktsukamo <ktsukamo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 23:12:26 by nyoshimi          #+#    #+#             */
/*   Updated: 2024/08/17 20:55:00 by ktsukamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	fatal_error(const char *msg)
{
	ft_printf_fd(2, "Fatal Error: %s\n", msg);
	exit(1);
}

void	validate_path(char **argv, t_var **list, t_tool *tool)
{
	char	*value;
	char	**env;

	value = ft_getenv(list, "PATH");
	if (!value)
	{
		env = list_to_environ(list);
		if (execve(argv[0], argv, env) == -1)
		{
			free_argv(env);
			put_error_message(argv[0], NULL, tool);
			exit(127);
		}
		free_argv(env);
	}
}

void	put_export_error(char *arg, t_tool *tool)
{
	tool->status = 1;
	ft_putstr_fd("expert: '", 2);
	ft_putstr_fd(arg, 2);
	ft_putendl_fd("': not a valid identifier", 2);
}

void	put_error_message(char *argv, char *message, t_tool *tool)
{
	tool->status = 1;
	if (tool->filename)
	{
		ft_printf_fd(2, "%s: line %d:", tool->filename, tool->line_count);
	}
	else
		ft_putstr_fd("minishell: ", 2);
	ft_printf_fd(2, "%s: ", argv);
	if (message)
		ft_putendl_fd(message, 2);
	else
		perror("");
}

void	put_heredoc_error(char *delimiter, t_tool *tool)
{
	if (tool->filename)
	{
		ft_printf_fd(2, "%s: line %d:", tool->filename, tool->line_count);
	}
	else
		ft_putstr_fd("minishell: ", 2);
	ft_printf_fd(2,
		"warning: here-document delimited by end-of-file (wanted `%s')\n",
		delimiter);
}
