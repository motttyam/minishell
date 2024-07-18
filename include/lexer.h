/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktsukamo <ktsukamo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 09:26:24 by nyoshimi          #+#    #+#             */
/*   Updated: 2024/07/17 22:08:36 by ktsukamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# define ARGMAX 2097152

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
}					t_lexer_state;

typedef struct s_fd
{
	int	saved_stdin;
	int	saved_stdout;
	int	saved_stderr;
}		t_fd;

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