/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktsukamo <ktsukamo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 13:04:47 by yoshiminaok       #+#    #+#             */
/*   Updated: 2024/08/18 15:34:13 by ktsukamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

typedef struct s_parser
{
	char	**argv;
	int		count;
	int		redirect_flag;
	t_var	**list;
	t_fd	fd;
}			t_parser;

typedef enum e_parser_state
{
	PIPE_AND_EXECVE = 0xe101,
	EXECVE_ONLY,
	FILE_ERROR,
}			t_parser_state;

// parser
void		parse_token(t_token *ptr, t_fd saved_fd, t_var **varlist,
				t_tool *tool);
void		parse_newline(t_token **ptr, t_parser *parser, t_tool *tool);
void		parse_pipe(t_token **ptr, t_parser *parser, t_tool *tool);
void		parse_redirect(t_token **ptr, t_parser *parser);
void		parse_command(t_token **ptr, t_parser *parser, t_tool *tool);
void		parse_command_without_redirect(t_token **ptr, t_parser *parser,
				t_tool *tool, int *i);
void		parse_command_redirect(t_token **ptr, t_parser *parser,
				t_tool *tool);
int			get_argsize(t_token *ptr);

// expand
char		*get_expanded_argv(char *token, t_var **varlist, int *status);
char		*get_keyname(char *token, int *i);
void		expand_opt_env(char **argv, char *key_name, t_var **varlist,
				int *status);
void		not_expand(char **argv, char *token, int *i);
void		get_status(char **argv, int *status);
void		join_noexpand_str(char **argv, int i, int start, char *token);

// redirect
int			redirect(t_token **ptr, t_tool *tool, t_parser *parser);
int			input_redirect(t_token **ptr, t_tool *tool, t_var **list);
int			save_heredoc(t_token *input);
int			output_redirect(t_token **ptr, t_tool *tool, t_var **list);
int			output_append(t_token **ptr, t_tool *tool, t_var **list);
void		redirect_close_and_dup(int *pipefd);
int			expand_file(t_token **ptr, t_tool *tool, t_var **list);

// pipe
void		pipe_close_and_dup(int *pipefd);
void		pipe_and_execute(char **cmd, int *count, t_parser *parser,
				t_tool *tool);

// interpret
void		read_file(char *file, t_tool *tool, t_fd saved_fd, t_var **list);

#endif