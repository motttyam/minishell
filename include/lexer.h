/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktsukamo <ktsukamo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 09:26:24 by nyoshimi          #+#    #+#             */
/*   Updated: 2024/07/07 19:04:19 by ktsukamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

typedef struct s_token
{
	char			*token;
	int				type;
	struct s_token	*next;
}					t_token;

typedef struct s_token_lexer
{
	t_token			*first;
	t_token			*current;
	int				line_i;
	// substrで必要な長さ
	int				token_i;
	// quote内でのspaceの処理フラグ 0,1,2
	int				in_quote;
}					t_token_lexer;

typedef enum e_token_type
{
	WORD = 0xc101,
	WORD_EXPANDED,
	QUOTE,
	PIPE,
	QUOTE_EXPANDED,
	INPUT_REDIRECTION,
	HEREDOCUMENT,
	OUTPUT_REDIRECTION,
	OUTPUT_APPENDING,
	NEWLINE,
}					token_type;

typedef enum e_lexer_state
{
	LEXSTAT_NORMAL = 0xd101,
	LEXSTAT_SINGLE_QUOTED,
	LEXSTAT_DOUBLE_QUOTED,
}	t_lexer_state;

void				lex_token(t_token_lexer *lexer, char *line);

#endif