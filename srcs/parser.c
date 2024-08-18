/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyoshimi <nyoshimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 08:53:11 by yoshiminaok       #+#    #+#             */
/*   Updated: 2024/08/18 15:43:11 by nyoshimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	parse_token(t_token *ptr, t_fd saved_fd, t_var **varlist, t_tool *tool)
{
	t_parser	parser;

	if (ptr == NULL)
		return ;
	parser.argv = NULL;
	parser.count = 0;
	parser.redirect_flag = PIPE_AND_EXECVE;
	parser.fd = saved_fd;
	parser.list = varlist;
	parse_newline(&ptr, &parser, tool);
	if (ptr == NULL && parser.argv)
	{
		if (parser.redirect_flag != FILE_ERROR)
		{
			interpret(parser.argv, parser.list, tool, &parser);
			close(STDIN_FILENO);
		}
		else
			tool->last_status = tool->status;
		free_argv(parser.argv);
		wait_for_all_process(parser.count, tool);
		if (parser.redirect_flag == FILE_ERROR)
			tool->status = tool->last_status;
	}
}

void	parse_newline(t_token **ptr, t_parser *parser, t_tool *tool)
{
	parse_pipe(ptr, parser, tool);
	while (*ptr)
	{
		if ((*ptr)->type == TK_NEWLINE)
		{
			if (parser->argv)
			{
				if (parser->redirect_flag != FILE_ERROR)
					interpret(parser->argv, parser->list, tool, parser);
				reinit_fd(parser->fd);
				wait_for_all_process(parser->count, tool);
				parser->count = 0;
				tool->line_count++;
				*ptr = (*ptr)->next;
				free_argv(parser->argv);
				parser->argv = NULL;
			}
			if ((*ptr) != NULL)
				parse_pipe(ptr, parser, tool);
		}
		else
			break ;
	}
}



void	parse_pipe(t_token **ptr, t_parser *parser, t_tool *tool)
{
	parse_command(ptr, parser, tool);
	while (*ptr)
	{
		if ((*ptr)->type == PIPE)
		{
			if (parser->redirect_flag == PIPE_AND_EXECVE)
				pipe_and_execute(parser->argv, &parser->count, parser, tool);
			else if (parser->redirect_flag == EXECVE_ONLY)
			{
				pipe_and_execute(parser->argv, &parser->count, parser, tool);
				parser->redirect_flag = PIPE_AND_EXECVE;
				dup2(parser->fd.saved_stdout, STDOUT_FILENO);
			}
			handle_file_error(parser);
			free_argv(parser->argv);
			*ptr = (*ptr)->next;
			parse_command(ptr, parser, tool);
		}
		else
			break ;
	}
}

void	parse_command(t_token **ptr, t_parser *parser, t_tool *tool)
{
	int	size;
	int	i;

	size = get_argsize(*ptr);
	i = 0;
	parser->argv = (char **)malloc(sizeof(char *) * (size + 1));
	if (!parser->argv)
		fatal_error("malloc");
	while (i < size)
	{
		parse_command_without_redirect(ptr, parser, tool, &i);
		parse_command_redirect(ptr, parser, tool);
	}
	parse_command_redirect(ptr, parser, tool);
	parser->argv[i] = NULL;
}
