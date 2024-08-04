/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktsukamo <ktsukamo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 09:53:36 by nyoshimi          #+#    #+#             */
/*   Updated: 2024/08/03 21:27:49 by ktsukamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	lex_token(t_token_lexer *lexer, char *line, t_tool *tool, int apenddflg)
{
	init_token_lexer(lexer, apenddflg);
	while (line[lexer->line_i])
	{
		if (line[lexer->line_i] != ' ' && line[lexer->line_i] != '\t')
		{
			get_token(lexer, line);
			if (validate_syntax(lexer, tool))
				return (1);
		}
		else
			lexer->line_i++;
	}
	if (lexer->current == NULL || check_last_token(lexer, tool))
		return (1);
	return (0);
}

void	init_token_lexer(t_token_lexer *lexer, int apendflg)
{
	lexer->line_i = 0;
	lexer->token_i = 0;
	lexer->in_quote = NORMAL;
	if (!apendflg)
	{
		lexer->first = NULL;
		lexer->current = NULL;
	}
}

void	get_token(t_token_lexer *lexer, char *line)
{
	ft_lstadd_new_token(lexer);
	if (line[lexer->line_i] == '|')
		get_pipe_token(lexer, line);
	else if (line[lexer->line_i] == '<' || line[lexer->line_i] == '>')
		get_redirect_token(lexer, line);
	else if (line[lexer->line_i] == '\n')
		get_newline_token(lexer, line);
	else
		get_word_token(lexer, line);
	lexer->current->token[lexer->token_i] = '\0';
}

void	get_tokenchar(t_token_lexer *lexer, char *line, char *token)
{
	token[lexer->token_i] = line[lexer->line_i];
	lexer->line_i++;
	lexer->token_i++;
}

void	ft_lstadd_new_token(t_token_lexer *lexer)
{
	t_token	*new;

	new = (t_token *)malloc(sizeof(t_token));
	if (!new)
		handle_malloc_error();
	if (lexer->first == NULL)
	{
		new->pre = NULL;
		new->next = NULL;
		lexer->first = new;
		lexer->current = new;
	}
	else
	{
		new->pre = lexer->current;
		new->next = NULL;
		lexer->current->next = new;
		lexer->current = new;
	}
	lexer->token_i = 0;
}
