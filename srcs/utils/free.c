/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktsukamo <ktsukamo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 13:46:01 by ktsukamo          #+#    #+#             */
/*   Updated: 2024/08/03 21:45:23 by ktsukamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_token_lexer(t_token *head)
{
	t_token	*current;

	while (head)
	{
		current = head;
		head = head->next;
		free(current);
	}
}

void	free_envlist(t_var *head)
{
	t_var	*current;

	while (head)
	{
		current = head;
		head = head->next;
		free(current->key);
		free(current->value);
		free(current);
	}
}

void	free_argv(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		free(argv[i]);
		i++;
	}
	free(argv);
}
