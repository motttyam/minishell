/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktsukamo <ktsukamo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 16:43:42 by nyoshimi          #+#    #+#             */
/*   Updated: 2024/08/18 16:11:48 by ktsukamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*get_expanded_argv(char *token, t_var **varlist, int *status)
{
	t_expand	expand;

	initialize_expand_struct(&expand);
	while (token[expand.i])
	{
		while (token[expand.i] == '$')
		{
			join_noexpand_str(&(expand.argv), expand.i, expand.start, token);
			(expand.i)++;
			expand.key_name = get_keyname(token, &(expand.i));
			if (expand.key_name == NULL)
			{
				not_expand(&(expand.argv), token, &(expand.i));
				expand.start = (expand.i)--;
				break ;
			}
			expand_opt_env(&(expand.argv), expand.key_name, varlist, status);
			free(expand.key_name);
			expand.start = (expand.i);
			(expand.i)--;
		}
		(expand.i)++;
	}
	join_noexpand_str(&(expand.argv), expand.i, expand.start, token);
	return (expand.argv);
}

char	*get_keyname(char *token, int *i)
{
	char	*key_name;
	int		start;

	start = *i;
	while (1)
	{
		if (*i == start && token[*i] == '?')
		{
			(*i)++;
			break ;
		}
		if (*i == start && !ft_isalpha(token[*i]))
			break ;
		if (*i != start && !ft_isalnum(token[*i]) && token[*i] != '_')
			break ;
		(*i)++;
	}
	if (start == *i)
		return (NULL);
	key_name = ft_substr(token, start, *i - start);
	if (!key_name)
		fatal_error("malloc");
	return (key_name);
}

void	expand_opt_env(char **argv, char *key_name, t_var **varlist,
		int *status)
{
	t_var	*opt;
	char	*tmp;

	opt = *varlist;
	if (key_name[0] == '?')
		return (get_status(argv, status));
	while (opt)
	{
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

void	not_expand(char **argv, char *token, int *i)
{
	char	*no_expand;
	char	*tmp;
	int		start;

	start = *i;
	while (token[*i] != '$' && token[*i] != '\0')
		(*i)++;
	no_expand = ft_substr(token, start - 1, *i - start + 1);
	if (!no_expand)
		fatal_error("malloc");
	tmp = *argv;
	*argv = ft_strjoin(*argv, no_expand);
	if (!*argv)
		fatal_error("malloc");
	free(tmp);
	free(no_expand);
}

void	get_status(char **argv, int *status)
{
	char	*tmp;
	char	*status_str;

	tmp = *argv;
	if (save_sig_status(-1) == SIG_NORMAL)
		*argv = ft_strjoin(*argv, "130");
	else
	{
		if (*status > 256)
			status_str = ft_itoa(*status / 256);
		else
			status_str = ft_itoa(*status);
		*argv = ft_strjoin(*argv, status_str);
		free(status_str);
	}
	if (!*argv)
		fatal_error("malloc");
	free(tmp);
}
