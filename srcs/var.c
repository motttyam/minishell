/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyoshimi <nyoshimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 14:05:01 by nyoshimi          #+#    #+#             */
/*   Updated: 2024/07/17 20:54:38 by nyoshimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_var *get_new_var(int i);
void	add_last_newvar(t_var **first,t_var *new);

t_var ** get_envlist()
{
	int	i;
	t_var **lst;
	t_var *first;

	if (!environ || !environ[0])
		return (NULL);
	first = get_new_var(0);
	lst = &first;
	i = 1;
	while (environ[i])
	{
		add_last_newvar(lst,get_new_var(i));
		i++;
	}
	return (lst);
}

t_var *get_new_var(int i)
{
	t_var	*new;
	int j;
	int	value_start;
	
	j = 0;
	new =(t_var *)malloc(sizeof(t_var));
	while(environ[i][j] != '=')
		j++;
	new->key = ft_substr(environ[i],0,j);
	if(!new->key)
		fatal_error("malloc");
	value_start = j + 1;
	while(environ[i][j] != '\0')
		j++;
	new->value = ft_substr(environ[i],value_start,j - value_start);
	if(!new->value)
		fatal_error("malloc");
	new->next = NULL;
	return (new);
}

void	add_last_newvar(t_var **first,t_var *new)
{
	t_var	*tmp;

	tmp = *first;
	while(tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
}