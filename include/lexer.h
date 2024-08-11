/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktsukamo <ktsukamo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 09:26:24 by nyoshimi          #+#    #+#             */
/*   Updated: 2024/08/11 18:43:03 by ktsukamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# define ARGMAX 2097152

// tool
typedef struct s_tool
{
	int				status;
	int				last_status;
	int				execve_flg;
	char			*home;
	char			*pwd;
	char			*input;
	char			*filename;
	int				line_count;
	char			*ps1;
	char			*ps2;
	char			pwd_first[PATH_MAX];
}					t_tool;

// var.h
typedef struct s_var
{
	char			*key;
	char			*value;
	int				type;
	struct s_var	*next;
}					t_var;

typedef struct s_token
{
	char			token[ARGMAX];
	int				type;
	struct s_token	*next;
	struct s_token	*pre;
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

typedef struct s_fd
{
	int				saved_stdin;
	int				saved_stdout;
	int				saved_stderr;
}					t_fd;

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

int					lex_token(t_token_lexer *lexer, char *line, t_tool *tool,
						int apendflg);
void				init_token_lexer(t_token_lexer *lexer, int apendflg);
void				get_token(t_token_lexer *lexer, char *line);
void				get_tokenchar(t_token_lexer *lexer, char *line,
						char *token);
void				ft_lstadd_new_token(t_token_lexer *lexer);
int					check_last_token(t_token_lexer *lexer, t_tool *tool,
						char *line);

// token
void				get_pipe_token(t_token_lexer *lexer, char *line);
void				get_newline_token(t_token_lexer *lexer, char *line);
void				get_redirect_token(t_token_lexer *lexer, char *line);
void				get_word_token(t_token_lexer *lexer, char *line);
int					process_word_token(t_token_lexer *lexer, char *line);
void				get_doublequote_token(t_token_lexer *lexer, char *line);
void				get_singlequote_token(t_token_lexer *lexer, char *line);
void				get_redirect_fd_token(t_token_lexer *lexer, char *line);

// syntax
int					validate_syntax(t_token_lexer *lexer, t_tool *tool);
void				put_syntax_error(char *token, t_tool *tool);

// heredoc
void				get_heredoc_input(t_token *delimiter, t_var **list,
						int *status, t_tool *tool);
char				*get_input_noexpand(t_token *delimiter, t_tool *tool);
char				*get_input_expand(t_token *delimiter, t_var **list,
						int *status, t_tool *tool);
void				put_heredoc_error(char *delimiter, t_tool *tool);
void				expand_and_append_line(t_var **list, int *status,
						char *line, char **buf);

#endif