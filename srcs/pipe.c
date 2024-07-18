/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyoshimi <nyoshimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 12:15:25 by yoshiminaok       #+#    #+#             */
/*   Updated: 2024/07/18 20:36:34 by nyoshimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	pipe_and_execute(char **cmd,int *count)
{
	int pipefd[2];
	pid_t pid;

	(*count)++;
	if (pipe(pipefd) == -1)
		fatal_error("pipe");
	pid = fork();
	if (pid == -1)
		fatal_error("fork");
	if (pid == 0)
	{
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		close(pipefd[0]);
		do_child_process(cmd);
	}
	else
	{
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
		close(pipefd[1]);
	}
}