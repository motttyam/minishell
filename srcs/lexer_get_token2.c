/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_get_token2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktsukamo <ktsukamo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 21:28:36 by ktsukamo          #+#    #+#             */
/*   Updated: 2024/08/04 14:06:56 by ktsukamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	get_doublequote_token(t_token_lexer *lexer, char *line)
{
	lexer->in_quote = DOUBLE_QUOTED;
	lexer->current->type = DOUBLE_QUOTE;
	lexer->line_i++;
	while (line[lexer->line_i])
	{
		if (line[lexer->line_i] == '"')
		{
			lexer->line_i++;
			lexer->in_quote = NORMAL;
		}
		else if (line[lexer->line_i] == '\\')
		{
			if (ft_strchr("\\`$", line[lexer->line_i + 1]))
				lexer->line_i++;
		}
		else if (line[lexer->line_i] == '$')
			lexer->current->type = QUOTE_EXPANDED;
		if (lexer->in_quote == NORMAL && ft_strchr("|<>\n \t",
				line[lexer->line_i]))
			break ;
		get_tokenchar(lexer, line, lexer->current->token);
	}
}

void	get_singlequote_token(t_token_lexer *lexer, char *line)
{
	lexer->in_quote = SINGLE_QUOTED;
	lexer->current->type = SINGLE_QUOTE;
	lexer->line_i++;
	while (line[lexer->line_i])
	{
		if (line[lexer->line_i] == '\'')
		{
			lexer->line_i++;
			lexer->in_quote = NORMAL;
		}
		if (lexer->in_quote == NORMAL && ft_strchr("|<>\n \t",
				line[lexer->line_i]))
			break ;
		get_tokenchar(lexer, line, lexer->current->token);
	}
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
