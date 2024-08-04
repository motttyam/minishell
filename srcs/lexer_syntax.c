/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktsukamo <ktsukamo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 09:53:36 by nyoshimi          #+#    #+#             */
/*   Updated: 2024/08/04 14:01:38 by ktsukamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	put_syntax_error(char *token, t_tool *tool)
{
	if (tool->filename)
	{
		ft_printf_fd(2, "%s: line %d:", tool->filename, tool->line_count);
	}
	else
		ft_putstr_fd("minishell: ", 2);
	ft_printf_fd(2, "syntax error near unexpected token `%s'\n", token);
}

int	validate_syntax(t_token_lexer *lexer, t_tool *tool)
{
	if ((lexer->current->pre != NULL
			&& (lexer->current->type == INPUT_REDIRECTION
				|| lexer->current->type == HEREDOCUMENT
				|| lexer->current->type == OUTPUT_REDIRECTION
				|| lexer->current->type == OUTPUT_APPENDING)
			&& (lexer->current->pre->type == INPUT_REDIRECTION
				|| lexer->current->pre->type == HEREDOCUMENT
				|| lexer->current->pre->type == OUTPUT_REDIRECTION
				|| lexer->current->pre->type == OUTPUT_APPENDING))
		|| (lexer->current->type == PIPE && (lexer->current->pre == NULL
				|| lexer->current->pre->type == INPUT_REDIRECTION
				|| lexer->current->pre->type == HEREDOCUMENT
				|| lexer->current->pre->type == OUTPUT_REDIRECTION
				|| lexer->current->pre->type == OUTPUT_APPENDING)))
	{
		put_syntax_error(lexer->current->token, tool);
		if (lexer->current->pre != NULL)
			lexer->current->pre->type = WORD;
		lexer->current->type = WORD;
		return (1);
	}
	return (0);
}
