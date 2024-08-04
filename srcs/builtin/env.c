/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktsukamo <ktsukamo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 16:50:06 by ktsukamo          #+#    #+#             */
/*   Updated: 2024/08/04 20:36:16 by ktsukamo         ###   ########.fr       */
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

void	exec_env(char **argv, t_var **list, t_tool *tool)
{
	int		i;
	char	**env;

	i = 1;
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

char	**list_to_environ(t_var **list)
{
	t_var	*head;
	char	**env;
	char	**top;
	char	*tmp;

	allocate_env(&env, list);
	top = env;
	head = *list;
	while (head)
	{
		if (head->value != NULL)
		{
			*env = ft_strjoin(head->key, "=");
			tmp = *env;
			*env = ft_strjoin(*env, head->value);
			free(tmp);
			env++;
		}
		head = head->next;
	}
	*env = NULL;
	return (top);
}

void	allocate_env(char ***env, t_var **list)
{
	t_var	*head;
	int		i;

	i = 0;
	head = *list;
	while (head)
	{
		if (head->value != NULL)
			i++;
		head = head->next;
	}
	*env = (char **)malloc(sizeof(char *) * (i + 1));
	if (!env)
		fatal_error("malloc");
}
