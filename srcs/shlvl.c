/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyoshimi <nyoshimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 13:53:12 by nyoshimi          #+#    #+#             */
/*   Updated: 2024/08/13 17:54:02 by nyoshimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	set_shlvl(t_var **list,t_tool *tool)
{
	t_var	*shlvl_node;
	int		shlvl;

	shlvl_node = NULL;
	ft_getenv_node(list, "SHLVL", &shlvl_node);
	if (!shlvl_node)
	{
		export_arg("SHLVL=1",list,tool);
		return ;
	}
	shlvl = ft_atoi(shlvl_node->value);
	shlvl++;
	if (shlvl >= 1000)
	{
		ft_printf_fd(2, "minishell: warning: shell level (%d) ", shlvl);
		ft_printf_fd(2, "too high, resetting to 1\n");
		shlvl = 1;
	}
	free(shlvl_node->value);
	shlvl_node->value = ft_itoa(shlvl);
	if (!shlvl_node->value)
		fatal_error("malloc");
}

void	reset_shlvl(t_var **list)
{
	t_var	*shlvl_node;

	shlvl_node = NULL;
	ft_getenv_node(list, "SHLVL", &shlvl_node);
	if (!shlvl_node)
		return ;
	free(shlvl_node->value);
	shlvl_node->value = ft_itoa(0);
	if (!shlvl_node->value)
		fatal_error("malloc");
}

void	validate_shlvl(t_var **list)
{
	t_var	*shlvl_node;

	shlvl_node = NULL;
	ft_getenv_node(list, "SHLVL", &shlvl_node);
	if (!shlvl_node)
		return ;
	if (ft_atoi(shlvl_node->value) < 0)
	{
		free(shlvl_node->value);
		shlvl_node->value = ft_itoa(0);
		if (!shlvl_node->value)
			fatal_error("malloc");
	}
}
