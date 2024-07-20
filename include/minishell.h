/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktsukamo <ktsukamo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 17:19:56 by nyoshimi          #+#    #+#             */
/*   Updated: 2024/07/20 15:17:52 by ktsukamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "error.h"
# include "lexer.h"
# include "libft.h"
# include "var.h"
# include "parser.h"
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
void					interpret(char **argv, int *count, t_var **list);
void					do_child_process(char **argv, t_var **list);
void					wait_for_all_process(int count);
void					pipe_and_execute(char **cmd, int *count, t_var **list);
void					reinit_fd(t_fd saved_fd);

#endif
