/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktsukamo <ktsukamo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 09:53:36 by nyoshimi          #+#    #+#             */
/*   Updated: 2024/08/03 21:24:57 by ktsukamo         ###   ########.fr       */
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

void	get_newline_token(t_token_lexer *lexer, char *line)
{
	get_tokenchar(lexer, line, lexer->current->token);
	lexer->current->type = TK_NEWLINE;
}

void	get_word_token(t_token_lexer *lexer, char *line)
{
	lexer->current->type = WORD;
	while (line[lexer->line_i])
	{
		if (lexer->in_quote == NORMAL && line[lexer->line_i] == '\'')
		{
			get_singlequote_token(lexer, line);
			break ;
		}
		else if (lexer->in_quote == NORMAL && line[lexer->line_i] == '"')
		{
			get_doublequote_token(lexer, line);
			break ;
		}
		else if (lexer->in_quote == NORMAL && line[lexer->line_i] == '$')
			lexer->current->type = WORD_EXPANDED;
		else if (lexer->in_quote == NORMAL && ft_strchr("<>",
				line[lexer->line_i]))
		{
			get_redirect_fd_token(lexer, line);
			break ;
		}
		else if (lexer->in_quote == NORMAL && line[lexer->line_i] == '\\')
		{
			lexer->line_i++;
			continue ;
		}
		else if (lexer->in_quote == NORMAL && ft_strchr("|\n \t",
				line[lexer->line_i]))
			break ;
		get_tokenchar(lexer, line, lexer->current->token);
	}
	if (lexer->in_quote != NORMAL)
		quote_error();
}

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
