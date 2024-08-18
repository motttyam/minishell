/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyoshimi <nyoshimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 09:53:36 by nyoshimi          #+#    #+#             */
/*   Updated: 2024/08/18 01:18:21 by nyoshimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	lex_token(t_token_lexer *lexer, char *line, t_tool *tool, int apenddflg)
{
	char	*tmp;

	tmp = NULL;
	init_token_lexer(lexer, apenddflg);
	while (line[lexer->line_i])
	{
		if (line[lexer->line_i] != ' ' && line[lexer->line_i] != '\t')
		{
			get_token(lexer, line);
			if (validate_syntax(lexer, tool))
			{
				tool->status = 2;
				return (1);
			}
		}
		else
			lexer->line_i++;
	}
	if (lexer->current == NULL || check_last_token(lexer, tool, tmp))
	{
		tool->status = 2;
		return (1);
	}
	return (0);
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
