/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktsukamo <ktsukamo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 20:55:09 by ktsukamo          #+#    #+#             */
/*   Updated: 2024/07/27 15:15:57 by ktsukamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	change_directory(char *argv, t_var **list, t_tool *tool)
{
	t_var	*current;
	char	*tmp;
	char	*tmp2;
	char	path[PATH_MAX];

	current = *list;
	tmp = NULL;
	tmp2 = NULL;
	if (chdir(argv) == 0)
	{
		if (getcwd(path, sizeof(path)) == NULL)
		{
			perror("minishell: cd:");
			return ;
		}
		ft_getenv_node(list, "PWD", &current);
		if (current != NULL)
		{
			tmp = current->value;
			current->value = ft_strdup(path);
			tmp2 = tool->pwd;
			tool->pwd = ft_strdup(path);
		}
		else
		{
			tmp2 = tool->pwd;
			tool->pwd = ft_strdup(path);
		}
		ft_getenv_node(list, "OLDPWD", &current);
		if (current != NULL)
		{
			free(current->value);
			if (tmp != NULL)
			{
				current->value = tmp;
				if (tmp2 != NULL && tmp2 != tmp)
					free(tmp2);
			}
			else
				current->value = tmp2;
		}
		else
		{
			if(tmp != NULL)
				free(tmp);
			if(tmp2 != NULL && tmp2 != tmp)
				free(tmp);
		}
	}
	else
	{
		printf("%s\n", argv);
		perror("minishell: cd");
	}
}

void	exec_cd(char **argv, t_var **list, t_tool *tool)
{
	struct stat info;
	char *tmp;

	if (ft_argvlen(argv) >= 3)
	{
		ft_putstr_fd("minishell: cd: too many arguments", 2);
		return ;
	}
	else if (ft_argvlen(argv) == 1)
	{
		change_directory(ft_getenv(list, "HOME"), list, tool);
		return ;
	}
	if(argv[1][0] == '~')
	{
		tmp = *(argv + 1);
		*(argv + 1) = ft_strjoin(tool->home, *(argv + 1) + 1);
		free(tmp);
	}
	if (stat(argv[1], &info) == 0)
	{
		if (S_ISDIR(info.st_mode))
		{
			change_directory(argv[1], list, tool);
		}
		else
		{
			ft_putstr_fd("minishell: cd:", 2);
			ft_putstr_fd(argv[1], 2);
			ft_putendl_fd(": Not a directory", 2);
		}
	}
	else
	{
		perror("minishell: cd");
	}
}