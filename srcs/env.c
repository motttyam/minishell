/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyoshimi <nyoshimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 16:50:06 by ktsukamo          #+#    #+#             */
/*   Updated: 2024/07/20 18:46:59 by nyoshimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_argvlen(char **argv)
{
	int	i;

	i = 0;
	if (argv == NULL)
		return (0);
	while (*argv)
	{
		argv++;
		i++;
	}
	return (i);
}

void	exec_env(char **argv, t_var **list)
{
	int		i;
	char	**env;

	i = 1;
	if (ft_argvlen(argv) >= 2)
	{
		ft_putstr_fd("env: '", 2);
		ft_putstr_fd(argv[1], 2);
		ft_putendl_fd("': No such file or directory", 2);
        return ;
	}
	env = list_to_environ(list);
	if (env == NULL)
		return ;
    i = 0;
	while (env[i])
	{
		ft_putendl_fd(env[i], 1);
        i++;
	}
    i = 0;
    while (env[i])
        free(env[i++]);
    free(env);
	return ;
}