/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktsukamo <ktsukamo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 17:06:27 by nyoshimi          #+#    #+#             */
/*   Updated: 2024/07/28 14:55:57 by ktsukamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// volatile t_signal_state g_signal = {0, 0};

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

int	main(void)
{
	t_var			*first;
	t_token_lexer	lexer;
	t_fd			saved_fd;
	t_tool			tool;

	save_fd(&saved_fd);
	setup_signal_handler();
	first = NULL;
	get_envlist(&first);
	tool.status = 0;
	tool.home = ft_strdup(ft_getenv(&first, "HOME"));
	tool.pwd = ft_strdup(ft_getenv(&first, "PWD"));
	while (1)
	{
		tool.input = NULL;
		tool.input = rl_input();
		if (!tool.input)
			break ;
		lex_token(&lexer, tool.input);
		check_heredoc_token(lexer.first, &first, &(tool.status));
		parse_token(lexer.first, saved_fd, &first, &tool);
		free_token_lexer(lexer.first);
		reinit_fd(saved_fd);
	}
	close_fd(saved_fd);
	free(tool.home);
	free(tool.pwd);
	free_envlist(first);
	ft_putendl_fd("exit", 2);
	return (0);
}
