/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktsukamo <ktsukamo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 16:50:06 by ktsukamo          #+#    #+#             */
/*   Updated: 2024/07/28 18:27:52 by ktsukamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

    // permissonがないときもあるかも
	if (ft_argvlen(argv) >= 2)
	{
		ft_printf_fd(2, "env: '%s' No such file or directory\n");
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
