/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshiminaoki <yoshiminaoki@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 17:19:56 by nyoshimi          #+#    #+#             */
/*   Updated: 2024/07/12 13:24:50 by yoshiminaok      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "error.h"
# include "lexer.h"
# include "parser.h"
# include "libft.h"
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

# define PROMPT "minshell $ "

extern char **environ;
char	*rl_input(void);
char	*search_path(const char *line);
// int		interpret(char *line);
int		interpret(char **cmd);
void pipe_and_execute(char  **cmd);

#endif