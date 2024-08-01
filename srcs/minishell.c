/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyoshimi <nyoshimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 17:06:27 by nyoshimi          #+#    #+#             */
/*   Updated: 2024/08/02 05:28:29 by nyoshimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

volatile t_signal_state	g_signal = {0, 0};

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
void lex_and_parse(char *line,t_tool *tool,t_fd saved_fd,t_var **list)
{
	t_token_lexer	lexer;
	
	if(lex_token(&lexer, line,tool) == -1)
	{
		check_heredoc_token(lexer.first,list,&tool->status,tool);
		return ;
	}
	check_heredoc_token(lexer.first,list,&tool->status,tool);
	parse_token(lexer.first, saved_fd, list, tool);
	free_token_lexer(lexer.first);
	reinit_fd(saved_fd);
}

int	main(void)
{
	t_var			*first;
	t_fd			saved_fd;
	t_tool			tool;

	save_fd(&saved_fd);
	setup_signal_handler();
	first = NULL;
	get_envlist(&first);
	tool.status = 0;
	tool.filename = NULL;
	tool.line_count = 1;
	tool.ps1 = NULL;
	tool.ps2 = NULL;
	tool.home = ft_strdup(ft_getenv(&first, "HOME"));
	tool.pwd = ft_strdup(ft_getenv(&first, "PWD"));
	while (1)
	{
		tool.input = NULL;
		tool.input = rl_input(&tool,&first);
		if (!tool.input)
			break ;
		lex_and_parse(tool.input,&tool,saved_fd,&first);
	}
	close_fd(saved_fd);
	free(tool.home);
	free(tool.pwd);
	free_envlist(first);
	ft_putendl_fd("exit", 2);
	return (0);
}
