/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktsukamo <ktsukamo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 17:06:27 by nyoshimi          #+#    #+#             */
/*   Updated: 2024/08/03 21:48:35 by ktsukamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

volatile t_signal_state	g_signal = {0, 0, 0};

void	lex_and_parse(char *line, t_tool *tool, t_fd saved_fd, t_var **list)
{
	t_token_lexer	lexer;

	if (lex_token(&lexer, line, tool, 0))
	{
		check_heredoc_token(lexer.first, list, &tool->status, tool);
		return ;
	}
	if (check_heredoc_token(lexer.first, list, &tool->status, tool) != -1)
		parse_token(lexer.first, saved_fd, list, tool);
	free_token_lexer(lexer.first);
	reinit_fd(saved_fd);
}

void	init_tool(t_tool *tool, t_var *first)
{
	tool->status = 0;
	tool->filename = NULL;
	tool->line_count = 1;
	tool->ps1 = NULL;
	tool->ps2 = NULL;
	tool->home = ft_strdup(ft_getenv(&first, "HOME"));
	tool->pwd = ft_strdup(ft_getenv(&first, "PWD"));
}

void	reinit_tool_and_signal(t_tool *tool)
{
	g_signal.sigint = 0;
	g_signal.is_child = 0;
	tool->input = NULL;
}

int	main(void)
{
	t_var	*first;
	t_fd	saved_fd;
	t_tool	tool;

	save_fd(&saved_fd);
	setup_signal_handler();
	first = NULL;
	get_envlist(&first);
	init_tool(&tool, first);
	while (1)
	{
		reinit_tool_and_signal(&tool);
		tool.input = rl_input(&tool, &first);
		if (!tool.input)
			break ;
		lex_and_parse(tool.input, &tool, saved_fd, &first);
	}
	close_fd(saved_fd);
	free(tool.home);
	free(tool.pwd);
	free(tool.ps1);
	free(tool.ps2);
	free_envlist(first);
	ft_putendl_fd("exit", 2);
	return (0);
}
