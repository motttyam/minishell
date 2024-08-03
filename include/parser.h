/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktsukamo <ktsukamo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 13:04:47 by yoshiminaok       #+#    #+#             */
/*   Updated: 2024/08/03 20:55:26 by ktsukamo         ###   ########.fr       */
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

void		parse_token(t_token *ptr, t_fd saved_fd, t_var **varlist,
				t_tool *tool);
char		*get_expanded_argv(char *token, t_var **varlist, int *status);

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

#endif