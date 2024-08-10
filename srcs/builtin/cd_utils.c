/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktsukamo <ktsukamo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 19:35:58 by ktsukamo          #+#    #+#             */
/*   Updated: 2024/08/10 21:48:08 by ktsukamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	save_oldpwd(t_var **list, char *tmp)
{
	t_var	*current;

	ft_getenv_node(list, "OLDPWD", &current);
	if (current != NULL)
	{
		free(current->value);
		if (tmp != NULL)
			current->value = tmp;
	}
}

void	save_tool_pwd(t_tool *tool, char *tmp2, char *path)
{
	tmp2 = tool->pwd;
	tool->pwd = ft_strdup(path);
	if (!tool->pwd)
		fatal_error("malloc");
	free(tmp2);
}

void	init_oldpwd(t_tool *tool, t_var **list, char *tmp2, char *path)
{
	t_var	*current;

	save_tool_pwd(tool, tmp2, path);
	ft_getenv_node(list, "OLDPWD", &current);
	if (current != NULL && current->value != NULL)
	{
		free(current->value);
		current->value = NULL;
	}
}

void	ft_getenv_node(t_var **list, char *key_name, t_var **opt)
{
	*opt = *list;
	while (*opt)
	{
		if (!ft_strncmp((*opt)->key, key_name, ft_strlen((*opt)->key) + 1))
			return ;
		*opt = (*opt)->next;
	}
	return ;
}
