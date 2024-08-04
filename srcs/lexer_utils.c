/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktsukamo <ktsukamo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 14:00:20 by ktsukamo          #+#    #+#             */
/*   Updated: 2024/08/04 14:14:49 by ktsukamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

int	check_last_token(t_token_lexer *lexer, t_tool *tool, char *line)
{
	int		result;

	if (lexer->current->type == INPUT_REDIRECTION
		|| lexer->current->type == HEREDOCUMENT
		|| lexer->current->type == OUTPUT_REDIRECTION
		|| lexer->current->type == OUTPUT_APPENDING)
	{
		put_syntax_error("newline", tool);
		lexer->current->type = WORD;
		return (1);
	}
	if (lexer->current->type == PIPE)
	{
		if (tool->ps2)
			line = readline(tool->ps2);
		else
			line = readline("> ");
		if (!line)
			return (put_error_message("syntax error", "unexpected end of file",
					tool), 1);
		result = lex_token(lexer, line, tool, 1);
		free(line);
		return (result);
	}
	return (0);
}
