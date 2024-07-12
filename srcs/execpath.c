/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execpath.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshiminaoki <yoshiminaoki@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 16:33:23 by ktsukamo          #+#    #+#             */
/*   Updated: 2024/07/12 21:48:28 by yoshiminaok      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// int interpret (char *line)
// {
// 	extern char **environ;
// 	char *argv[] = {line, NULL};
// 	pid_t pid;
// 	int wstatus;

// 	pid = fork();
// 	if (pid < 0)
// 		fatal_error("fork");
// 	else if (pid == 0)
// 	{
// 		execve(line, argv, environ);
// 		fatal_error("execve");
// 	}
// 	else
// 	{
// 		wait(&wstatus);
// 		return(WEXITSTATUS(wstatus));
// 	}
// }

//parserのテスト用に書き換えて使ってます
int interpret (char **argv)
{
	// extern char **environ;
	pid_t pid;
	// int wstatus;
	if (ft_strchr(argv[0], '/') == NULL)
		argv[0] = search_path(argv[0]); 
	pid = fork();
	if (pid < 0)
		fatal_error("fork");
	else if (pid == 0)
	{
		execve(argv[0], argv, environ);
		fatal_error("execve");
	}
	else
	{
		waitpid(-1,NULL,0);
		return(0);
	}
}