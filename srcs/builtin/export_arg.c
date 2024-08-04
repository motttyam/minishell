/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_arg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktsukamo <ktsukamo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 16:41:29 by nyoshimi          #+#    #+#             */
/*   Updated: 2024/08/04 16:48:20 by ktsukamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
	{
		update_env_var(opt, append_flg, newvalue);
		free(keyname);
	}
	else
		add_last_newvar(*list, export_new_var(keyname, newvalue));
}

void	update_env_var(t_var *opt, int append_flg, char *newvalue)
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

int	get_env_keyname(char *arg, char **key_name)
{
	int	i;
	int	append_flg;

	i = 0;
	append_flg = 0;
	while (arg[i] != '=' && arg[i] != '+' && arg[i])
	{
		if (i == 0 && ft_isdigit(arg[i]))
			put_export_error(arg);
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
			put_export_error(arg);
		i++;
	}
	*key_name = ft_substr(arg, 0, i);
	if (!key_name)
		fatal_error("malloc");
	if (arg[i] == '+')
	{
		i++;
		if (arg[i] != '=')
			put_export_error(arg);
		append_flg = 1;
	}
	return (append_flg);
}

char	*get_value(char *arg)
{
	int		i;
	int		start;
	char	*value;

	i = 0;
	while (arg[i] != '=' && arg[i])
		i++;
	if (arg[i] == '\0')
		return (NULL);
	start = i + 1;
	while (arg[i])
		i++;
	value = ft_substr(arg, start, i);
	if (!value)
		fatal_error("malloc");
	return (value);
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
