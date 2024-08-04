/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utlis.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktsukamo <ktsukamo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 19:40:12 by ktsukamo          #+#    #+#             */
/*   Updated: 2024/08/03 20:08:53 by ktsukamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	put_export_error(char *arg)
{
	ft_putstr_fd("expert: '", 2);
	ft_putstr_fd(arg, 2);
	ft_putendl_fd("': not a valid identifier", 2);
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
