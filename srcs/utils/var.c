/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktsukamo <ktsukamo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 23:38:42 by ktsukamo          #+#    #+#             */
/*   Updated: 2024/08/17 15:22:19 by ktsukamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_var	*set_new_envlist(void);

void	get_envlist(t_var **list)
{
	int			i;
	t_var		*first;
	extern char	**environ;

	if (!environ || !environ[0])
	{
		first = set_new_envlist();
		*list = first;
		return ;
	}
	first = get_new_var(0, environ);
	*list = first;
	i = 1;
	while (environ[i])
	{
		add_last_newvar(first, get_new_var(i, environ));
		i++;
	}
}

t_var	*get_new_var(int i, char **environ)
{
	t_var	*new;
	int		j;
	int		value_start;

	j = 0;
	new = (t_var *)malloc(sizeof(t_var));
	while (environ[i][j] != '=')
		j++;
	new->key = ft_substr(environ[i], 0, j);
	if (!new->key)
		fatal_error("malloc");
	value_start = j + 1;
	while (environ[i][j] != '\0')
		j++;
	new->value = ft_substr(environ[i], value_start, j - value_start);
	if (!new->value)
		fatal_error("malloc");
	new->next = NULL;
	new->type = ENV;
	return (new);
}

void	add_last_newvar(t_var *first, t_var *new)
{
	t_var	*tmp;

	tmp = first;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
}

t_var	*set_new_envlist(void)
{
	t_var	*oldpwd_var;
	t_var	*pwd_var;
	char	path[PATH_MAX];

	oldpwd_var = (t_var *)malloc(sizeof(t_var));
	oldpwd_var->key = ft_strdup("OLDPWD");
	if (!oldpwd_var->key)
		fatal_error("malloc");
	oldpwd_var->value = NULL;
	pwd_var = (t_var *)malloc(sizeof(t_var));
	oldpwd_var->next = pwd_var;
	pwd_var->next = NULL;
	pwd_var->key = ft_strdup("PWD");
	if (!pwd_var->key)
		fatal_error("malloc");
	getcwd(path, sizeof(path));
	pwd_var->value = ft_strdup(path);
	if (!pwd_var->value)
		fatal_error("malloc");
	return (oldpwd_var);
}
