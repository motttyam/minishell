/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyoshimi <nyoshimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 18:47:57 by ktsukamo          #+#    #+#             */
/*   Updated: 2024/08/11 12:31:15 by nyoshimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_list_remove_if(t_var **list, char *argv, int (cmp)())
{
	t_var	*current;

	if (!list || !(*list))
		return ;
	current = *list;
	if (cmp(argv, current->key, ft_strlen(argv) + 1) == 0)
	{
		*list = current->next;
		free(current->key);
		free(current->value);
		free(current);
		ft_list_remove_if(list, argv, cmp);
	}
	else
	{
		current = *list;
		ft_list_remove_if(&current->next, argv, cmp);
	}
}

void	exec_unset(char **argv, t_var **list, t_tool *tool)
{
	int	i;

	i = 1;
	tool->status = 0;
	if (!argv || !argv[0])
		return ;
	while (argv[i])
	{
		if (ft_strncmp(argv[i], "SHLVL", ft_strlen(argv[i]) != 0)
		&& ft_strncmp(argv[i], "_", ft_strlen(argv[i]) != 0))
			ft_list_remove_if(list, argv[i], ft_strncmp);
		i++;
	}
}
