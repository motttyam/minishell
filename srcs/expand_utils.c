/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktsukamo <ktsukamo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 15:10:29 by nyoshimi          #+#    #+#             */
/*   Updated: 2024/08/11 18:45:50 by ktsukamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	join_noexpand_str(char **argv, int i, int start, char *token)
{
	char	*str;
	char	*tmp;

	if (start == 0)
	{
		*argv = ft_substr(token, start, i);
		if (!argv)
			fatal_error("malloc");
	}
	else if (start != i)
	{
		str = ft_substr(token, start, i - start);
		if (!str)
			fatal_error("malloc");
		tmp = *argv;
		*argv = ft_strjoin(*argv, str);
		if (!*argv)
			fatal_error("malloc");
		free(str);
		free(tmp);
	}
}
