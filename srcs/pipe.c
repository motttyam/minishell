/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshiminaoki <yoshiminaoki@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 12:15:25 by yoshiminaok       #+#    #+#             */
/*   Updated: 2024/07/12 21:52:40 by yoshiminaok      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void pipe_and_execute(char  **cmd)
{
    int pipefd[2];
    pid_t pid;

    if (pipe(pipefd) == -1)
        fatal_error("pipe");
    pid = fork();
    if (pid == -1)
        fatal_error("fork");
    if (pid == 0)
    {
        dup2(pipefd[1],STDOUT_FILENO);
        close(pipefd[1]);
        close(pipefd[0]);
        if (ft_strchr(cmd[0], '/') == NULL)
		    cmd[0] = search_path(cmd[0]); 
        execve(cmd[0],cmd,environ);
    }
    else
    {
        dup2(pipefd[0],STDIN_FILENO);
        close(pipefd[0]);
        close(pipefd[1]);
        waitpid(-1,NULL,0);
    }
}