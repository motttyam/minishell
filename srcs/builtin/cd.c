/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktsukamo <ktsukamo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 20:55:09 by ktsukamo          #+#    #+#             */
/*   Updated: 2024/08/11 15:47:01 by ktsukamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	fatal_error_strdup(char *str)
{
	if (!str)
		fatal_error("malloc");
}

void	change_directory(char *argv, t_var **list, t_tool *tool)
{
	t_var	*current;
	char	*tmp;
	char	*tmp2;
	char	path[PATH_MAX];

	tmp = NULL;
	tmp2 = NULL;
	if (chdir(argv) == 0)
	{
		if (getcwd(path, sizeof(path)) == NULL)
			return (perror("minishell: cd:"));
		tool->status = 0;
		ft_getenv_node(list, "PWD", &current);
		if (current != NULL)
		{
			tmp = current->value;
			current->value = ft_strdup(path);
			fatal_error_strdup(current->value);
			return (save_tool_pwd(tool, tmp2, path), save_oldpwd(list, tmp));
		}
		else
			init_oldpwd(tool, list, tmp2, path);
	}
	else
		ft_printf_fd(2, "minishell: cd: %s: Permission Deined\n", argv);
}

int	check_dash_tilde(char **argv, t_var **list, t_tool *tool)
{
	char	*tmp;

	if ((argv[1][0] == '~' && argv[1][1] == '\0') || (argv[1][0] == '~'
			&& argv[1][1] == '/'))
	{
		tmp = *(argv + 1);
		return (*(argv + 1) = ft_strjoin(tool->home, *(argv + 1) + 1),
			free(tmp), 0);
	}
	if (argv[1][0] == '-')
	{
		if (argv[1][1] != '\0')
		{
			tool->status = 2;
			return (ft_printf_fd(2, "minishell: cd: %c%c: invalid option\n",
					argv[1][0], argv[1][1]), -1);
		}
		else if (ft_getenv(list, "OLDPWD") == NULL)
			return (tool->status = 1, (void)ft_printf_fd(2,
					"minishell: cd: OLDPWD not set\n"), -1);
		tmp = *(argv + 1);
		*(argv + 1) = ft_strjoin(ft_getenv(list, "OLDPWD"), *(argv + 1) + 1);
		return (free(tmp), (void)ft_printf_fd(1, "%s\n", *(argv + 1)), 0);
	}
	return (0);
}

void	exec_cd(char **argv, t_var **list, t_tool *tool)
{
	struct stat	info;

	tool->status = 1;
	if (ft_argvlen(argv) >= 3)
		return ((void)ft_printf_fd(2, "minishell: cd: too many arguments\n"));
	else if (ft_argvlen(argv) == 1)
	{
		if (ft_getenv(list, "HOME") == NULL)
			return ((void)ft_printf_fd(2, "bash: cd: HOME not set\n"));
		return (change_directory(ft_getenv(list, "HOME"), list, tool));
	}
	if (check_dash_tilde(argv, list, tool) != 0)
		return ;
	if (stat(argv[1], &info) == 0)
	{
		if (S_ISDIR(info.st_mode))
			change_directory(argv[1], list, tool);
		else
			ft_printf_fd(2, "minishell: cd: %s: Not a directory\n", argv[1]);
	}
	else
	{
		ft_printf_fd(2, "minishell: cd: %s: ", argv[1]);
		perror("");
	}
}
