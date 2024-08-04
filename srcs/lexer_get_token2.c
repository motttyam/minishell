/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_get_token2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktsukamo <ktsukamo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 21:28:36 by ktsukamo          #+#    #+#             */
/*   Updated: 2024/08/03 21:33:18 by ktsukamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	get_pipe_token(t_token_lexer *lexer, char *line)
{
	get_tokenchar(lexer, line, lexer->current->token);
	lexer->current->type = PIPE;
}

void	get_redirect_fd_token(t_token_lexer *lexer, char *line)
{
	int	i;

	i = 0;
	while (i < lexer->token_i)
	{
		if (!ft_isdigit(lexer->current->token[i]))
			return ;
		i++;
	}
	get_redirect_token(lexer, line);
}
