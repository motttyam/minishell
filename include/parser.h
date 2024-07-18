/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktsukamo <ktsukamo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 13:04:47 by yoshiminaok       #+#    #+#             */
/*   Updated: 2024/07/17 23:18:28 by ktsukamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

typedef struct s_parser
{
	char	**argv;
	int		count;
	int		redirect_flag;
	t_var	**varlist;
	t_fd	fd;
}			t_parser;

typedef enum e_parser_state
{
	PIPE_AND_EXECVE = 0xe101,
	EXECVE_ONLY,
	FILE_ERROR,
}			t_parser_state;

void		parse_token(t_token *ptr, t_fd saved_fd, t_var **varlist);
char		*get_expanded_argv(char *token, t_var **varlist);
int			redirect(t_token **ptr);

#endif