/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyoshimi <nyoshimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 19:38:44 by nyoshimi          #+#    #+#             */
/*   Updated: 2024/08/04 21:19:22 by nyoshimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	exec_pwd(t_var **list, t_tool *tool)
{
	char	*dir;
	char	path[PATH_MAX];

	dir = ft_getenv(list, "PWD");
	if (dir)
		ft_putendl_fd(dir, 1);
	else if (tool->pwd)
		ft_putendl_fd(tool->pwd, 1);
	else
		ft_putendl_fd(getcwd(path, sizeof(path)), 1);
	tool->status = 0;
}

char	*ft_getenv(t_var **list, char *key_name)
{
	t_var	*current;

	current = *list;
	while (current)
	{
		if (!ft_strncmp(current->key, key_name, ft_strlen(current->key) + 1))
			return (current->value);
		current = current->next;
	}
	return (NULL);
}
