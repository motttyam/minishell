/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktsukamo <ktsukamo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 19:38:44 by nyoshimi          #+#    #+#             */
/*   Updated: 2024/07/22 23:15:45 by ktsukamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void exec_pwd(t_var    **list)
{
    char    *dir;
    
    dir = ft_getenv(list,"PWD");
    if (dir)
        ft_putendl_fd(dir,1);
    else
    {   
        if ((getcwd(dir, PATH_MAX) != NULL))
            ft_putendl_fd(getcwd(dir,PATH_MAX),1);
        else
            perror("getcwd() error");
    }
}

char *ft_getenv(t_var    **list,char *key_name)
{
    t_var   *current;

    current = *list;
    while(current)
    {
        if(!ft_strncmp(current->key,key_name,ft_strlen(current->key) + 1))
            return (current->value);
        current = current->next;
    }
    return (NULL);
}