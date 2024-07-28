/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktsukamo <ktsukamo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 17:06:27 by nyoshimi          #+#    #+#             */
/*   Updated: 2024/07/28 13:55:21 by ktsukamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// volatile t_signal_state g_signal = {0, 0};

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
	tool.home = ft_getenv(&first, "HOME");
	tool.pwd = ft_getenv(&first, "PWD");
	while (1)
	{
		tool.input = NULL;
		tool.input = rl_input();
		if (!tool.input)
			break ;
		lex_token(&lexer, tool.input);
		check_heredoc_token(lexer.first, &first, &(tool.status));
		parse_token(lexer.first, saved_fd, &first, &tool);
		reinit_fd(saved_fd);
	}
	close_fd(saved_fd);
	ft_putendl_fd("exit", 2);
	return (0);
}
