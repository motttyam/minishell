/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyoshimi <nyoshimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 17:19:56 by nyoshimi          #+#    #+#             */
/*   Updated: 2024/08/13 15:59:10 by nyoshimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <errno.h>
# include <fcntl.h>
// # include <limits.h>
# include "ft_printf.h"
# include "get_next_line.h"
# include "libft.h"
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
# include "parser.h"
# include "builtin.h"
# include "utils.h"

extern volatile sig_atomic_t	g_sig;

# define PROMPT "minishell $ "

void							lex_and_parse(char *line, t_tool *tool,
									t_fd saved_fd, t_var **list);
int								check_syntaxerror(t_token *token, int *status);
void							handle_signal(int signal);
char							*rl_input(t_tool *tool, t_var **list);
char							*search_path(const char *line, t_var **list);
void							interpret(char **argv, t_var **list,
									t_tool *tool, t_parser *parser);
void							do_child_process(char **argv, t_var **list,
									t_tool *tool, t_fd saved_fd);
void							do_path_command(char **argv, t_var **list,
									t_tool *tool, t_fd saved_fd);
void							pipe_and_execute(char **cmd, int *count,
									t_parser *parser, t_tool *tool);
void							reinit_fd(t_fd saved_fd);
int								check_heredoc_token(t_token *token,
									t_var **list, int *status, t_tool *tool);
void							wait_for_all_process(int count, t_tool *tool);
void							free_argv(char **argv);
void							init_tool(t_var **list, t_tool *tool);

typedef enum e_signal_state
{
	SIG_INIT,
	SIG_NORMAL,
	SIG_HEREDOC,
	SIG_CHILD,
}								t_signal_state;

// signal
void							setup_signal_handler(void);
void							heredoc_signal_handler(void);
void							ignore_signal_handler(void);
void							handle_interactive(int signal);
void							handle_heredoc(int signal);
void							execve_signal_handler(void);
int								save_sig_status(int flag);
void							handle_execve(int signal);

// shlvl
void							set_shlvl(t_var **list,t_tool *tool);
void							reset_shlvl(t_var **list);
void							validate_shlvl(t_var **list);
#endif
