/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyoshimi <nyoshimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 16:31:39 by nyoshimi          #+#    #+#             */
/*   Updated: 2024/08/04 16:42:15 by nyoshimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	exec_export(t_var **list, char **argv, int count)
{
	int	i;

	i = 1;
	if (ft_argvlen(argv) == 1)
		sort_and_put_env(list);
	else if (!count)
	{
		while (argv[i])
		{
			export_arg(argv[i], list);
			i++;
		}
	}
}

void	sort_and_put_env(t_var **list)
{
	t_var	*current;
	t_var	*save;
	char	*pre_save;
	int		save_flg;

	current = *list;
	save = current;
	save_flg = 0;
	pre_save = NULL;
	while (1)
	{
		save_opt_env(current,&save,pre_save,&save_flg);	
		if (current->next == NULL)
		{
			if (save_flg)
				put_env(save);
			else
				return ;
			current = *list;
			save_flg = 0;
			pre_save = save->key;
		}
		current = current->next;
	}
}

void	save_opt_env(t_var *current, t_var **save, char *pre_save, int *save_flg)
{
	if ((!pre_save || (pre_save && ft_strncmp(pre_save, current->key,
				ft_strlen(pre_save) + 1) < 0)) && ((*save)->key == pre_save
		|| (ft_strncmp((*save)->key, current->key, ft_strlen((*save)->key)
				+ 1) > 0)))
	{
		(*save) = current;
		*save_flg = 1;
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

void	put_export_error(char *arg)
{
	ft_putstr_fd("expert: '", 2);
	ft_putstr_fd(arg, 2);
	ft_putendl_fd("': not a valid identifier", 2);
}