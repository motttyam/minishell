/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktsukamo <ktsukamo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 00:10:48 by ktsukamo          #+#    #+#             */
/*   Updated: 2024/07/14 16:25:51 by ktsukamo         ###   ########.fr       */
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
