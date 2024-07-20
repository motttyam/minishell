/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktsukamo <ktsukamo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 16:43:42 by nyoshimi          #+#    #+#             */
/*   Updated: 2024/07/20 14:35:34 by ktsukamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*get_keyname(char *token, int *i);
void	expand_opt_env(char **argv, char *key_name, t_var **varlist);

char	*get_expanded_argv(char *token, t_var **varlist)
{
	int		i;
	char	*argv;
	char	*key_name;

	i = 0;
	argv = NULL;
	while (token[i])
	{
		while (token[i] == '$')
		{
			if (argv == NULL)
				argv = ft_substr(token, 0, i);
			i++;
			key_name = get_keyname(token, &i);
			expand_opt_env(&argv, key_name, varlist);
			i--;
		}
		i++;
	}
	printf("argv = %s", argv);
	return (argv);
}

char	*get_keyname(char *token, int *i)
{
	char	*key_name;
	int		start;

	start = *i;
	while (token[*i] && token[*i] != '$')
		(*i)++;
	key_name = ft_substr(token, start, *i - start);
	if (!key_name)
		fatal_error("malloc");
	return (key_name);
}

void	expand_opt_env(char **argv, char *key_name, t_var **varlist)
{
	t_var	*opt;
	char	*tmp;

	opt = *varlist;
	while (opt)
	{
		// printf("keyname = %s\n", key_name);
		// printf("opt->key = %s\n", opt->key);
		if (!ft_strncmp(key_name, opt->key, ft_strlen(key_name) + 1))
			break ;
		opt = opt->next;
	}
	if (opt == NULL)
		return ;
	tmp = *argv;
	*argv = ft_strjoin(*argv, opt->value);
	if (!*argv)
		fatal_error("malloc");
	free(tmp);
}
