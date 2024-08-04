/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktsukamo <ktsukamo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 21:25:10 by nyoshimi          #+#    #+#             */
/*   Updated: 2024/08/04 20:02:23 by ktsukamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_heredoc_token(t_token *token, t_var **list, int *status, t_tool *tool)
{
	while (token)
	{
		if (token->type == HEREDOCUMENT)
		{
			token = token->next;
			g_signal.is_heredoc = 1;
			get_heredoc_input(token, list, status, tool);
			if (g_signal.is_heredoc == 2)
			{
				g_signal.is_heredoc = 0;
				*status = 130;
				return (-1);
			}
			g_signal.is_heredoc = 0;
		}
		token = token->next;
	}
	return (0);
}

void	get_heredoc_input(t_token *delimiter, t_var **list, int *status,
		t_tool *tool)
{
	char	*buf;

	if (delimiter->type == SINGLE_QUOTE || delimiter->type == DOUBLE_QUOTE
		|| delimiter->type == QUOTE_EXPANDED)
		buf = get_input_noexpand(delimiter, tool);
	else
		buf = get_input_expand(delimiter, list, status, tool);
	ft_bzero(delimiter->token, ft_strlen(delimiter->token));
	delimiter->type = WORD;
	if (g_signal.is_heredoc == 2)
	{
		if (buf)
			free(buf);
		return ;
	}
	else if (!buf)
		return ;
	ft_strlcpy(delimiter->token, buf, PATH_MAX);
	free(buf);
}

char	*get_input_noexpand(t_token *delimiter, t_tool *tool)
{
	char	*line;
	char	*buf;

	buf = NULL;
	while (1)
	{
		if (tool->ps2)
			line = readline(tool->ps2);
		else
			line = readline("> ");
		if (g_signal.is_heredoc == 2)
			return (buf);
		else if (!line)
			return (put_heredoc_error(delimiter->token, tool), buf);
		if (!ft_strncmp(line, delimiter->token, ft_strlen(delimiter->token)
				+ 1))
			break ;
		buf = ft_strjoinendl(buf, line);
		free(line);
	}
	return (buf);
}

void	expand_and_append_line(t_var **list, int *status, char *line, char *buf)
{
	char	*tmp;

	if (ft_strchr(line, '$'))
	{
		tmp = line;
		line = get_expanded_argv(line, list, status);
		free(tmp);
	}
	buf = ft_strjoinendl(buf, line);
	free(line);
}

char	*get_input_expand(t_token *delimiter, t_var **list, int *status,
		t_tool *tool)
{
	char	*line;
	char	*buf;

	buf = NULL;
	while (1)
	{
		if (tool->ps2)
			line = readline(tool->ps2);
		else
			line = readline("> ");
		if (g_signal.is_heredoc == 2)
			return (buf);
		else if (!line)
			return (put_heredoc_error(delimiter->token, tool), buf);
		if (!ft_strncmp(line, delimiter->token, ft_strlen(delimiter->token)
				+ 1))
			break ;
		expand_and_append_line(list, status, line, buf);
	}
	return (buf);
}
