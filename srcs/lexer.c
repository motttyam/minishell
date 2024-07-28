/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktsukamo <ktsukamo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 09:53:36 by nyoshimi          #+#    #+#             */
/*   Updated: 2024/07/28 21:15:39 by ktsukamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	get_singlequote_token(t_token_lexer *lexer, char *line);

void	lex_token(t_token_lexer *lexer, char *line)
{
	init_token_lexer(lexer);
	while (line[lexer->line_i])
	{
		if (line[lexer->line_i] != ' ' && line[lexer->line_i] != '\t')
			get_token(lexer, line);
		else
			lexer->line_i++;
	}
}

void	init_token_lexer(t_token_lexer *lexer)
{
	lexer->line_i = 0;
	lexer->token_i = 0;
	lexer->in_quote = NORMAL;
	lexer->first = NULL;
	lexer->current = NULL;
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

void	get_pipe_token(t_token_lexer *lexer, char *line)
{
	get_tokenchar(lexer, line, lexer->current->token);
	lexer->current->type = PIPE;
}

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
			get_singlequote_token(lexer,line);
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
		}
		else if (lexer->in_quote == NORMAL && ft_strchr("|\n \t",
				line[lexer->line_i]))
		{
			// lexer->current->token[lexer->token_i] = '\0';
			break ;
		}
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

char	*ft_strchr(const char *str, int c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ((unsigned char)str[i] == (unsigned char)c)
			return ((char *)&str[i]);
		i++;
	}
	if ((char)c == '\0')
		return ((char *)&str[i]);
	return (0);
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
		new->next = NULL;
		lexer->first = new;
		lexer->current = new;
	}
	else
	{
		new->next = NULL;
		lexer->current->next = new;
		lexer->current = new;
	}
	lexer->token_i = 0;
}
