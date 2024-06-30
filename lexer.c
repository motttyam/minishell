/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyoshimi <nyoshimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 09:53:36 by nyoshimi          #+#    #+#             */
/*   Updated: 2024/06/29 21:07:59 by nyoshimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstadd_new_token(t_token_lexer *lexer,char *line)
{
	t_token *new;
	
	new = (t_token *)malloc(sizeof(t_token));
	if (!new)
		handle_malloc_error();
	if (lexer->first == NULL)
	{
		new->token = ft_substr(line,0,lexer->token_i);
		new->next = NULL;
		lexer->first = new;
		lexer->current = new;
	}
	else
	{
		new->token = ft_substr(line,lexer->line_i - lexer->token_i,lexer->token_i);
		new->next = NULL;
		lexer->current->next = new;
		lexer->current = new;
	}
	lexer->token_i = 0;
}

void init_token_lexer(t_token_lexer *lexer)
{
	lexer->line_i = 0;
	lexer->token_i = 0;
	lexer->in_quote = 0;
	lexer->first = NULL;
	lexer->current = NULL;
}

void get_redirect_token(t_token_lexer *lexer, char *line)
{
	lexer->line_i++;
	lexer->token_i++;
	if(line[lexer->line_i] == line[lexer->line_i - 1])
	{
		lexer->line_i++;
		lexer->token_i++;
	}
	ft_lstadd_new_token(lexer,line);
	lexer->current->type= TYPE_REDIRECT;
}

void make_token_list(t_token_lexer *lexer, char *line)
{
	while(line[lexer->line_i])
	{
		if(lexer->in_quote == 0 && line[lexer->line_i] == '\'')
		{
			lexer->in_quote = 1;
			lexer->line_i++;
			lexer->token_i++;
		}
		if(lexer->in_quote == 0 && line[lexer->line_i] == '"')
		{
			lexer->in_quote = 2;
			lexer->line_i++;
			lexer->token_i++;
		}
		if(lexer->in_quote == 0 &&ft_strchr("|\n \t",line[lexer->line_i]))
		{
			ft_lstadd_new_token(lexer,line);
			lexer->current->type= TYPE_WORD;
			break ;
		}
		if(lexer->in_quote == 0 &&ft_strchr("<>",line[lexer->line_i]))
		{
			//もし"2>"等に対応するなら修正必要
			ft_lstadd_new_token(lexer,line);
			lexer->current->type= TYPE_WORD;
			break ;
		}
		if((lexer->in_quote == 1 && line[lexer->line_i] == '\'')
			|| (lexer->in_quote == 2 && line[lexer->line_i] == '"'))
		{
			lexer->line_i++;
			lexer->token_i++;
			// if (line[lexer->line_i] == ' ')
			lexer->in_quote = 0;
		}
		lexer->line_i++;
		lexer->token_i++;
	}
	if (lexer->token_i > 0 && line[lexer->line_i] == '\0')
	{
		ft_lstadd_new_token(lexer,line);
		lexer->current->type= TYPE_WORD;
	}
}

void get_token(t_token_lexer *lexer, char *line)
{
	if(line[lexer->line_i] == '|')
	{
		lexer->line_i++;
		lexer->token_i++;
		ft_lstadd_new_token(lexer,line);
		lexer->current->type= TYPE_PIPE;
	}
	else if(ft_strchr("<>",line[lexer->line_i]))
		get_redirect_token(lexer,line);
	else
		make_token_list(lexer,line);
}

void lex_token(t_token_lexer *lexer,char *line)
{
	init_token_lexer(lexer);
	while(line[lexer->line_i])
	{
		if(line[lexer->line_i] != ' ' && line[lexer->line_i] != '\t')
			get_token(lexer,line);
		else
			lexer->line_i++;
	}
}