/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyoshimi <nyoshimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 17:19:56 by nyoshimi          #+#    #+#             */
/*   Updated: 2024/07/24 21:48:30 by nyoshimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "error.h"
# include "lexer.h"
# include "libft.h"
# include "var.h"
# include "builtin.h"
# include "parser.h"
# include "support.h"
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
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

# define PROMPT "minshell $ "

typedef struct s_signal_state
{
	int					status;
	int					signal_child_received;
	int					heredoc_interruption;
}						t_signal_state;
extern t_signal_state	g_signal;

char					*rl_input(void);
char					*search_path(const char *line);
// int		interpret(char *line);
char					**list_to_environ(t_var **list);
void					interpret(char **argv, int *count, t_var **list,int *status);
void					do_child_process(char **argv, t_var **listint);
void					wait_for_all_process(int count,int *status);
void					pipe_and_execute(char **cmd, int *count, t_var **list,int *status);
void					reinit_fd(t_fd saved_fd);
void					check_heredoc_token(t_token *token, t_var **list);

#endif
