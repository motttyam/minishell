/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyoshimi <nyoshimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 16:31:39 by nyoshimi          #+#    #+#             */
/*   Updated: 2024/08/13 17:46:18 by nyoshimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	exec_export(t_var **list, char **argv, int count, t_tool *tool)
{
	int	i;

	i = 1;
	tool->status = 0;
	if (ft_argvlen(argv) == 1)
		sort_and_put_env(list);
	else if (!count)
	{
		while (argv[i])
		{
			export_arg(argv[i], list, tool);
			i++;
		}
	}
}
int get_envlist_size(t_var **list)
{
	t_var *tmp;
	int size;

	tmp = *list;
	size = 0;
	while(tmp)
	{
		tmp = tmp->next;
		size++;
	}
	return (size);
}

void	sort_and_put_env(t_var **list)
{
	t_var	*current;
	t_var	*save;
	char	*pre_save;
	int		size;

	current = *list;
	save = current;
	pre_save = NULL;
	size = get_envlist_size(list);
	while (1)
	{
		save_opt_env(current, &save, pre_save);
		if (current->next == NULL)
		{
			put_env(save);
			current = *list;
			pre_save = save->key;
			size--;
			if (!size)
				return ;
		}
		current = current->next;
	}
}

void	save_opt_env(t_var *current, t_var **save, char *pre_save)
{
	if ((!pre_save || (pre_save && ft_strncmp(pre_save, current->key,
					ft_strlen(pre_save) + 1) < 0)) && ((*save)->key == pre_save
			|| (ft_strncmp((*save)->key, current->key, ft_strlen((*save)->key)
					+ 1) > 0)))
	{
		(*save) = current;
	}
}

void	put_env(t_var *save)
{
	if (!ft_strncmp(save->key, "_", 2))
		return ;
	ft_putstr_fd("declare -x ", 1);
	ft_putstr_fd(save->key, 1);
	if (save->value)
	{
		ft_putstr_fd("=\"", 1);
		ft_putstr_fd(save->value, 1);
		ft_putendl_fd("\"", 1);
	}
	else
		ft_putstr_fd("\n", 1);
}

void	put_export_error(char *arg, t_tool *tool)
{
	tool->status = 1;
	ft_putstr_fd("expert: '", 2);
	ft_putstr_fd(arg, 2);
	ft_putendl_fd("': not a valid identifier", 2);
}
