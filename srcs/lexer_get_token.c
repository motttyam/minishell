/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_get_token.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktsukamo <ktsukamo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 09:53:36 by nyoshimi          #+#    #+#             */
/*   Updated: 2024/08/04 14:07:22 by ktsukamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	get_redirect_token(t_token_lexer *lexer, char *line)
{
	if (line[lexer->line_i] == '>' && line[lexer->line_i + 1] != '>')
	{
		get_tokenchar(lexer, line, lexer->current->token);
		lexer->current->type = OUTPUT_REDIRECTION;
	}
	if (line[lexer->line_i] == '>' && line[lexer->line_i + 1] == '>')
	{
		get_tokenchar(lexer, line, lexer->current->token);
		get_tokenchar(lexer, line, lexer->current->token);
		lexer->current->type = OUTPUT_APPENDING;
	}
	if (line[lexer->line_i] == '<' && line[lexer->line_i + 1] != '<')
	{
		get_tokenchar(lexer, line, lexer->current->token);
		lexer->current->type = INPUT_REDIRECTION;
	}
	if (line[lexer->line_i] == '<' && line[lexer->line_i + 1] == '<')
	{
		get_tokenchar(lexer, line, lexer->current->token);
		get_tokenchar(lexer, line, lexer->current->token);
		lexer->current->type = HEREDOCUMENT;
	}
}

void	get_pipe_token(t_token_lexer *lexer, char *line)
{
	get_tokenchar(lexer, line, lexer->current->token);
	lexer->current->type = PIPE;
}

void	get_newline_token(t_token_lexer *lexer, char *line)
{
	get_tokenchar(lexer, line, lexer->current->token);
	lexer->current->type = TK_NEWLINE;
}

void	get_word_token(t_token_lexer *lexer, char *line)
{
	int	res;

	res = 0;
	lexer->current->type = WORD;
	while (line[lexer->line_i])
	{
		res = process_word_token(lexer, line);
		if (res == 1)
			break ;
		else if (res == 0)
			continue ;
		get_tokenchar(lexer, line, lexer->current->token);
	}
	if (lexer->in_quote != NORMAL)
		quote_error();
}

int	process_word_token(t_token_lexer *lexer, char *line)
{
	if (lexer->in_quote == NORMAL && line[lexer->line_i] == '\'')
		return (get_singlequote_token(lexer, line), 1);
	else if (lexer->in_quote == NORMAL && line[lexer->line_i] == '"')
		return (get_doublequote_token(lexer, line), 1);
	else if (lexer->in_quote == NORMAL && ft_strchr("<>", line[lexer->line_i]))
		return (get_redirect_fd_token(lexer, line), 1);
	else if (lexer->in_quote == NORMAL && ft_strchr("|\n \t",
			line[lexer->line_i]))
		return (1);
	else if (lexer->in_quote == NORMAL && line[lexer->line_i] == '\\')
	{
		lexer->line_i++;
		return (0);
	}
	else if (lexer->in_quote == NORMAL && line[lexer->line_i] == '$')
	{
		lexer->current->type = WORD_EXPANDED;
		return (-1);
	}
	return (-1);
}
