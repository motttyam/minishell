/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execpath.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyoshimi <nyoshimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 16:33:23 by ktsukamo          #+#    #+#             */
/*   Updated: 2024/07/18 20:36:28 by nyoshimi         ###   ########.fr       */
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
        end = ft_strchr(value, ':');
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
            return ((char *)line);
        }
        value = end + 1;
    }
    // free(line);
    return ((char *)line);
}

//parserのテスト用に書き換えて使ってます
// int interpret (char **argv)
// {
// 	// extern char **environ;
// 	pid_t pid;
// 	// int wstatus;
// 	if (ft_strchr(argv[0], '/') == NULL)
// 		argv[0] = search_path(argv[0]); 
// 	pid = fork();
// 	if (pid < 0)
// 		fatal_error("fork");
// 	else if (pid == 0)
// 	{
// 		execve(argv[0], argv, environ);
// 		fatal_error("execve");
// 	}
// 	else
// 	{
// 		waitpid(-1,NULL,0);
// 		return(0);
// 	}
// }

void interpret (char **argv, int *count)
{
	pid_t	pid;
	
	(*count)++;
	pid = fork();
	if (pid < 0)
		fatal_error("fork");
	else if (pid == 0)
		do_child_process(argv);
}

void do_child_process(char **argv)
{
	if (ft_strchr(argv[0], '/'))
	{
		if (access(argv[0],X_OK) == -1)
			put_error_message(argv[0],0);
		else
			execve(argv[0], argv, environ);
	}
	else
	{
		argv[0] = search_path(argv[0]);
		execve(argv[0], argv, environ);
		put_error_message(argv[0], 1);
		exit(1);
	}
}

void wait_for_all_process(int count)
{
	int	i;

	i = 0;
	while(i < count)
	{
		waitpid(-1,NULL,0);
		i++;
	}
}