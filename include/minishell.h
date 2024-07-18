/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyoshimi <nyoshimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 17:19:56 by nyoshimi          #+#    #+#             */
/*   Updated: 2024/07/18 20:34:49 by nyoshimi         ###   ########.fr       */
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
// # include <linux/limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>

# define TEST printf("test\n\n")
# define PROMPT "minshell $ "

extern char	**environ;
char		*rl_input(void);
char		*search_path(const char *line);
// int		interpret(char *line);
void		interpret (char **argv, int *count);
void		do_child_process(char **argv);
void		wait_for_all_process(int count);
void		pipe_and_execute(char **cmd,int *count);
void		reinit_fd(t_fd saved_fd);

#endif
