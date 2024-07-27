/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktsukamo <ktsukamo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 17:19:56 by nyoshimi          #+#    #+#             */
/*   Updated: 2024/07/27 14:33:00 by ktsukamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <errno.h>
# include <fcntl.h>
// # include <limits.h>
# include <linux/limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_signal_state
{
	int					signal_child_received;
	int					heredoc_interruption;
}						t_signal_state;
extern t_signal_state	g_signal;

typedef struct s_tool
{
	int					status;
	char				*home;
	char				*pwd;
	char				*input;
	char				pwd_first[PATH_MAX];
}						t_tool;

# include "var.h"
# include "builtin.h"
# include "lexer.h"
# include "parser.h"
# include "error.h"
# include "libft.h"
# include "support.h"

# define PROMPT "minshell $ "

char					*rl_input(void);
char					*search_path(const char *line);
char					**list_to_environ(t_var **list);
void					interpret(char **argv, int *count, t_var **list,
							t_tool *tool);
void					do_child_process(char **argv, t_var **listint);
void					pipe_and_execute(char **cmd, int *count, t_var **list,
							t_tool *tool);
void					reinit_fd(t_fd saved_fd);

void					check_heredoc_token(t_token *token, t_var **list,
							int *status);
void					wait_for_all_process(int count, int *status);
#endif
