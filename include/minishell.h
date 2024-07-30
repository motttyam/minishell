/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyoshimi <nyoshimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 17:19:56 by nyoshimi          #+#    #+#             */
/*   Updated: 2024/07/31 02:29:22 by nyoshimi         ###   ########.fr       */
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
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include "lexer.h"
# include "libft.h"
#include "ft_printf.h"
# include "utils.h"
# include "parser.h"
# include "builtin.h"

typedef struct s_signal_state
{
	int							is_child;
	int							is_heredoc;
}								t_signal_state;

extern volatile t_signal_state	g_signal;

# define PROMPT "minishell $ "

int								check_syntaxerror(t_token *token, int *status);
void							handle_signal(int signal);
void							setup_signal_handler(void);
char							*rl_input(void);
char							*search_path(const char *line);
char							**list_to_environ(t_var **list);
void							interpret(char **argv, t_var **list, t_tool *tool,t_fd fd);
void							do_child_process(char **argv, t_var **listint);
void							pipe_and_execute(char **cmd, int *count,
									t_var **list, t_tool *tool);
void							reinit_fd(t_fd saved_fd);

int								check_heredoc_token(t_token *token, t_var **list, int *status);
void							wait_for_all_process(int count);
#endif
