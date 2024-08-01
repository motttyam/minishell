/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyoshimi <nyoshimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 16:31:39 by nyoshimi          #+#    #+#             */
/*   Updated: 2024/08/01 04:17:52 by nyoshimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	export_arg(char *arg, t_var **list);
void	ft_getenv_node(t_var **list, char *key_name, t_var **opt);
int		get_env_keyname(char *arg, char **key_name);
char	*get_value(char *arg);
t_var	*export_new_var(char *newkey, char *newvalue);
void	put_export_error(char *arg);
void	sort_and_put_env(t_var **list);
void	put_env(t_var *save);

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

void	export_arg(char *arg, t_var **list)
{
	int		append_flg;
	t_var	*opt;
	char	*keyname;
	char	*newvalue;
	char	*tmp;

	keyname = NULL;
	opt = NULL;
	append_flg = get_env_keyname(arg, &keyname);
	ft_getenv_node(list, keyname, &opt);
	newvalue = get_value(arg);
	if (opt)
	{
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
			//上の書き方malloc失敗したら怪しいかも
			if (!opt->value)
				fatal_error("malloc");
			free(tmp);
		}
	}
	else
		add_last_newvar(*list, export_new_var(keyname, newvalue));
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
		// free(key_name);
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

void	put_export_error(char *arg)
{
	ft_putstr_fd("expert: '", 2);
	ft_putstr_fd(arg, 2);
	ft_putendl_fd("': not a valid identifier", 2);
}