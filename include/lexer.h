/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktsukamo <ktsukamo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 09:26:24 by nyoshimi          #+#    #+#             */
/*   Updated: 2024/07/04 09:42:58 by ktsukamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
#define LEXER_H

typedef struct s_token
{
	char	*token;
	int		len;
	int		type;
	struct s_token	*next;
} 				t_token;

typedef struct s_token_lexer
{
	t_token	*first;
	t_token	*current;
	int		line_i;
	int		token_i;
	int		quote_i;
	int		in_quote;
}				t_token_lexer;
typedef enum e_token_type
{
	TYPE_PIPE,
	TYPE_REDIRECT,
	TYPE_WORD,
	TYPE_EXPANDED,
	TYPE_QUOTED_EXPANDED
} token_type;

void lex_token(t_token_lexer *lexer,char *line);

#endif