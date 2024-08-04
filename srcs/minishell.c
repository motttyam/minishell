/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktsukamo <ktsukamo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 17:06:27 by nyoshimi          #+#    #+#             */
/*   Updated: 2024/08/04 19:04:12 by ktsukamo         ###   ########.fr       */
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

void	init_tool(t_var **list, t_tool *tool)
{
	char	*home;
	char	*pwd;

	tool->status = 0;
	tool->filename = NULL;
	tool->line_count = 1;
	tool->home = NULL;
	tool->pwd = NULL;
	tool->ps1 = NULL;
	tool->ps2 = NULL;
	home = ft_getenv(list, "HOME");
	if (home)
		tool->home = ft_strdup(home);
	pwd = ft_getenv(list, "PWD");
	if (pwd)
		tool->pwd = ft_strdup(pwd);
}

void	reinit_tool_and_signal(t_tool *tool)
{
	g_signal.sigint = 0;
	g_signal.is_child = 0;
	tool->input = NULL;
}

void	fin_tool(t_tool *tool)
{
	if (tool->home)
		free(tool->home);
	if (tool->pwd)
		free(tool->pwd);
	if (tool->ps1)
		free(tool->ps1);
	if (tool->ps2)
		free(tool->ps2);
	if (g_signal.sigint == 1)
		tool->status = 130;
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
	init_tool(&first, &tool);
	while (1)
	{
		reinit_tool_and_signal(&tool);
		tool.input = rl_input(&tool, &first);
		if (!tool.input)
			break ;
		lex_and_parse(tool.input, &tool, saved_fd, &first);
	}
	close_fd(saved_fd);
	free_envlist(first);
	fin_tool(&tool);
	ft_putendl_fd("exit", 2);
	exit(tool.status);
	return (0);
}
