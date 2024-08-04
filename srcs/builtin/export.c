/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktsukamo <ktsukamo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 16:31:39 by nyoshimi          #+#    #+#             */
/*   Updated: 2024/08/03 20:35:50 by ktsukamo         ###   ########.fr       */
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
	pre_save = NULL;
	while (1)
	{
		save_flg = 0;
		if ((!pre_save || (pre_save && ft_strncmp(pre_save, current->key,
						ft_strlen(pre_save) + 1) < 0)) && (save->key == pre_save
				|| (ft_strncmp(save->key, current->key, ft_strlen(save->key)
						+ 1) > 0)))
		{
			save = current;
			save_flg = 1;
		}
		if (current->next == NULL)
		{
			if (!save_flg)
				return ;
			put_env(save);
			current = *list;
			pre_save = save->key;
		}
		current = current->next;
	}
}

void	update_env(t_var *opt, int append_flg, char *newvalue)
{
	char	*tmp;

	if (append_flg == 0)
	{
		if (newvalue)
		{
			free(opt->value);
			opt->value = newvalue;
		}
	}
	else
	{
		tmp = opt->value;
		opt->value = ft_strjoin(opt->value, newvalue);
		if (!opt->value)
			fatal_error("malloc");
		free(tmp);
	}
}

void	export_arg(char *arg, t_var **list)
{
	int		append_flg;
	t_var	*opt;
	char	*keyname;
	char	*newvalue;

	keyname = NULL;
	opt = NULL;
	append_flg = get_env_keyname(arg, &keyname);
	ft_getenv_node(list, keyname, &opt);
	newvalue = get_value(arg);
	if (opt)
		update_env(opt, append_flg, newvalue);
	else
		add_last_newvar(*list, export_new_var(keyname, newvalue));
}

t_var	*export_new_var(char *newkey, char *newvalue)
{
	t_var	*new;
	int		j;

	j = 0;
	new = (t_var *)malloc(sizeof(t_var));
	if (!new)
	{
		fatal_error("malloc");
	}
	new->key = newkey;
	new->value = newvalue;
	new->next = NULL;
	new->type = ENV;
	return (new);
}
