/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktsukamo <ktsukamo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 20:55:09 by ktsukamo          #+#    #+#             */
/*   Updated: 2024/07/20 22:26:58 by ktsukamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <sys/stat.h>
#include <sys/types.h>

void	change_directory(char *argv, t_var **list)
{
	t_var	*current;
	char	*tmp;
	char	path[PATH_MAX];

	current = *list;
    printf("%s\n", argv);
	if (chdir(argv) == 0)
	{
		if (getcwd(path, sizeof(path)) == NULL)
        {
            perror("minishell: cd:");
            return ;
        }
		while (ft_strncmp(current->key, "PWD", 4) != 0 && current)
		{
			current = current->next;
		}
		tmp = current->value;
		current->value = ft_strdup(path);
		current = *list;
		while (ft_strncmp(current->key, "OLDPWD", 7) != 0 && current)
		{
			current = current->next;
		}
		free(current->value);
		current->value = tmp;
	}
	else
	{
        printf("%s\n", argv);
		perror("minishell: cd");
	}
}

// ~(チルダ)未対応
void	exec_cd(char **argv, t_var **list)
{
	struct stat info;

	if (ft_argvlen(argv) >= 3)
	{
		ft_putstr_fd("minishell: cd: too many arguments", 2);
		return ;
	}
    else if (ft_argvlen(argv) == 1)
    {
        printf("hello\n");
        change_directory(ft_getenv(list, "HOME"), list);
        return ;
    }
	if (stat(argv[1], &info) == 0)
	{
		if (S_ISDIR(info.st_mode))
		{
			change_directory(argv[1], list);
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