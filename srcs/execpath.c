/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execpath.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktsukamo <ktsukamo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 16:33:23 by ktsukamo          #+#    #+#             */
/*   Updated: 2024/07/17 23:41:22 by ktsukamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char *search_path(const char *line)
{
    char path[PATH_MAX];
    char *value;
    char *end;

    value = getenv("PATH");
    while(*value)
    {
        bzero(path, PATH_MAX);
        end = strchr(value, ':');
        if (end)
            strncpy(path, value, end - value);
        else
            bzero(path, PATH_MAX);
        ft_strlcat(path, "/", PATH_MAX);
        ft_strlcat(path, line, PATH_MAX);
        if (access(path, X_OK) == 0)
        {
            char *dup;

            dup = strdup(path);
            if (dup == NULL)
                fatal_error("strdup");
            // free(line);
            return (dup);
        }
        if (end == NULL)
        {
            // free(line);
            return (NULL);
        }
        value = end + 1;
    }
    // free(line);
    return (NULL);
}

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