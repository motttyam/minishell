/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktsukamo <ktsukamo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 14:31:29 by ktsukamo          #+#    #+#             */
/*   Updated: 2024/08/10 20:51:16 by ktsukamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	get_argsize(t_token *ptr)
{
	t_token	*l;
	int		size;

	l = ptr;
	size = 0;
	while (l->type != PIPE && l->type != TK_NEWLINE)
	{
		if (l->type == INPUT_REDIRECTION || l->type == HEREDOCUMENT
			|| l->type == OUTPUT_REDIRECTION || l->type == OUTPUT_APPENDING)
		{
			l = l->next;
		}
		else
			size++;
		if (l->next == NULL)
			break ;
		l = l->next;
	}
	return (size);
}

void	parse_command_without_redirect(t_token **ptr, t_parser *parser,
		t_tool *tool, int *i)
{
	if (((*ptr)->type != INPUT_REDIRECTION && (*ptr)->type != HEREDOCUMENT
			&& (*ptr)->type != OUTPUT_REDIRECTION
			&& (*ptr)->type != OUTPUT_APPENDING))
	{
		if ((*ptr)->type == WORD_EXPANDED || (*ptr)->type == QUOTE_EXPANDED)
			parser->argv[*i] = get_expanded_argv((*ptr)->token, parser->list,
					&(tool->status));
		else
			parser->argv[*i] = ft_strdup((*ptr)->token);
		if (!parser->argv[*i])
			fatal_error("strdup");
		(*i)++;
		(*ptr) = (*ptr)->next;
	}
}

void	parse_command_redirect(t_token **ptr, t_parser *parser, t_tool *tool)
{
	while (((*ptr) && ((*ptr)->type == INPUT_REDIRECTION
				|| (*ptr)->type == HEREDOCUMENT
				|| (*ptr)->type == OUTPUT_REDIRECTION
				|| (*ptr)->type == OUTPUT_APPENDING)))
	{
		if ((*ptr)->type == HEREDOCUMENT)
			reinit_fd(parser->fd);
		parser->redirect_flag = redirect(ptr, tool, parser);
	}
}

void	wait_for_all_process(int count, t_tool *tool)
{
	int	i;

	i = 0;
	while (i < count)
	{
		waitpid(-1, &tool->status, 0);
		i++;
	}
	tool->status = tool->last_status;
	if (WIFEXITED(tool->status))
		tool->status = WEXITSTATUS(tool->status);
	else if (WIFSIGNALED(tool->status))
		tool->status = 128 + WTERMSIG(tool->status);
	setup_signal_handler();
}
