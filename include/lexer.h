/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktsukamo <ktsukamo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 09:26:24 by nyoshimi          #+#    #+#             */
/*   Updated: 2024/07/28 14:31:10 by ktsukamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# define ARGMAX 2097152

typedef struct s_token
{
	char			token[ARGMAX];
	int				type;
	struct s_token	*next;
}					t_token;

typedef struct s_token_lexer
{
	t_token			*first;
	t_token			*current;
	int				line_i;
	int				token_i;
	int				in_quote;
	int				is_expanded;
}					t_token_lexer;

typedef enum e_token_type
{
	WORD = 0,
	WORD_EXPANDED,
	SINGLE_QUOTE,
	DOUBLE_QUOTE,
	QUOTE_EXPANDED,
	PIPE,
	INPUT_REDIRECTION,
	HEREDOCUMENT,
	OUTPUT_REDIRECTION,
	OUTPUT_APPENDING,
	TK_NEWLINE,
}					t_token_type;

typedef enum e_lexer_state
{
	NORMAL = 0xd101,
	SINGLE_QUOTED,
	DOUBLE_QUOTED,
	NOT_EXPANDED,
	EXPANDED
}					t_lexer_state;

void				lex_token(t_token_lexer *lexer, char *line);
void				lex_token(t_token_lexer *lexer, char *line);
void				init_token_lexer(t_token_lexer *lexer);
void				get_token(t_token_lexer *lexer, char *line);
void				get_pipe_token(t_token_lexer *lexer, char *line);
void				get_newline_token(t_token_lexer *lexer, char *line);
void				get_redirect_token(t_token_lexer *lexer, char *line);
void				get_word_token(t_token_lexer *lexer, char *line);
void				get_doublequote_token(t_token_lexer *lexer, char *line);
void				get_redirect_fd_token(t_token_lexer *lexer, char *line);
char				*ft_strchr(const char *str, int c);
void				get_tokenchar(t_token_lexer *lexer, char *line,
						char *token);
void				ft_lstadd_new_token(t_token_lexer *lexer);

#endif