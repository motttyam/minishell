/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshiminaoki <yoshiminaoki@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 09:26:24 by nyoshimi          #+#    #+#             */
/*   Updated: 2024/07/09 18:10:18 by yoshiminaok      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

#define ARGMAX 2097152

typedef struct s_token
{
	char			token[ARGMAX];
	// char			*token;
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
	// 今扱っているtokenに$が含まれているか
	int				is_expanded;
}					t_token_lexer;

typedef enum e_token_type
{
	WORD = 0,
	WORD_EXPANDED,
	QUOTE,
	QUOTE_EXPANDED,
	PIPE,
	INPUT_REDIRECTION,
	HEREDOCUMENT,
	OUTPUT_REDIRECTION,
	OUTPUT_APPENDING,
	NEWLINE,
}					token_type;

typedef enum e_lexer_state
{
	NORMAL = 0xd101,
	SINGLE_QUOTED,
	DOUBLE_QUOTED,
	//$のフラグ
	NOT_EXPANDED,
	EXPANDED
}	t_lexer_state;

void				lex_token(t_token_lexer *lexer, char *line);

#endif