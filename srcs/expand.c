/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyoshimi <nyoshimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 16:43:42 by nyoshimi          #+#    #+#             */
/*   Updated: 2024/08/17 22:59:57 by nyoshimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*get_expanded_argv(char *token, t_var **varlist, int *status)
{
	int		i;
	char	*argv;
	char	*key_name;
	int		start;

	i = 0;
	start = 0;
	argv = NULL;
	while (token[i])
	{
		while (token[i] == '$')
		{
			join_noexpand_str(&argv, i, start, token);
			i++;
			key_name = get_keyname(token, &i);
			if (key_name == NULL)
			{
				not_expand(&argv,token,&i);
				start = i;
				i--;
				break;
			}
			expand_opt_env(&argv, key_name, varlist, status);
			free(key_name);
			start = i;
			i--;
		}
		i++;
	}
	join_noexpand_str(&argv, i, start, token);
	return (argv);
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
			break;
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

void	not_expand(char **argv,char *token, int *i)
{
	char	*no_expand;
	char	*tmp;
	int		start;

	start = *i;
	while(token[*i] != '$' && token[*i] != '\0')
		(*i)++;
	no_expand = ft_substr(token,start-1,*i - start +1);
	if (!no_expand)
		fatal_error("malloc");
	tmp = *argv;
	*argv = ft_strjoin(*argv,no_expand);
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
