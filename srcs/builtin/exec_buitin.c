/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_buitin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyoshimi <nyoshimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 15:00:56 by nyoshimi          #+#    #+#             */
/*   Updated: 2024/08/04 15:02:31 by nyoshimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	exec_builtin(char **argv, t_var **list, t_tool *tool, int count)
{
	if (argv[0] == NULL)
		return (0);
	if (ft_strncmp(argv[0], "echo", 5) == 0)
		return (exec_echo(argv), 0);
	else if (ft_strncmp(argv[0], "pwd", 4) == 0)
		return (exec_pwd(list, tool->pwd), 0);
	else if (ft_strncmp(argv[0], "export", 7) == 0)
		return (exec_export(list, argv, count), 0);
	else if (ft_strncmp(argv[0], "env", 4) == 0)
		return (exec_env(argv, list), 0);
	return (exec_builtin_based_on_pipe(argv,list,tool,count));
}

int	exec_builtin_based_on_pipe(char **argv, t_var **list, t_tool *tool, int count)
{
	if (ft_strncmp(argv[0], "cd", 3) == 0)
	{
		if(!count)
			exec_cd(argv, list, tool);
		return (0);
	}
	else if (ft_strncmp(argv[0], "unset", 6) == 0)
	{
		if(!count)
			exec_unset(argv, list);
		return (0);
	}
	else if (ft_strncmp(argv[0], "exit", 5) == 0)
	{
		if(!count)
			exec_exit(argv, &(tool->status), tool);
		return (0);
	}
	return (-1);
}