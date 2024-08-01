/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyoshimi <nyoshimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 21:25:10 by nyoshimi          #+#    #+#             */
/*   Updated: 2024/08/02 06:06:27 by nyoshimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	get_heredoc_input(t_token *delimiter, t_var **list, int *status,t_tool *tool);
char	*get_input_noexpand(t_token *delimiter,t_tool *tool);
char	*get_input_expand(t_token *delimiter, t_var **list, int *status,t_tool *tool);
void	put_heredoc_error(char *delimiter,t_tool *tool);

int	check_heredoc_token(t_token *token, t_var **list, int *status,t_tool *tool)
{
	while (token)
	{
		if (token->type == HEREDOCUMENT)
		{
			token = token->next;
			get_heredoc_input(token, list, status,tool);
		}
		token = token->next;
	}
	return (0);
}

void	get_heredoc_input(t_token *delimiter, t_var **list, int *status,t_tool *tool)
{
	char	*buf;

	if (delimiter->type == SINGLE_QUOTE || delimiter->type == DOUBLE_QUOTE
		|| delimiter->type == QUOTE_EXPANDED)
		buf = get_input_noexpand(delimiter,tool);
	else
		buf = get_input_expand(delimiter, list, status,tool);
	ft_bzero(delimiter->token, ft_strlen(delimiter->token));
	delimiter->type = WORD;
	if (!buf)
		return ;
	ft_strlcpy(delimiter->token, buf, PATH_MAX);
	free(buf);
}
char	*get_input_noexpand(t_token *delimiter,t_tool *tool)
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
		if (!line)
			return (put_heredoc_error(delimiter->token,tool),buf);
		if (!ft_strncmp(line, delimiter->token,ft_strlen(delimiter->token)+1))
			break ;
		buf = ft_strjoinendl(buf, line);
		free(line);
	}
	return (buf);
}

char	*get_input_expand(t_token *delimiter, t_var **list, int *status,t_tool *tool)
{
	char	*line;
	char	*buf;
	char	*tmp;

	buf = NULL;
	while (1)
	{
		if (tool->ps2)
			line = readline(tool->ps2);
		else
			line = readline("> ");
		if (!line)
			return (put_heredoc_error(delimiter->token,tool),buf);
		if (!ft_strncmp(line, delimiter->token,ft_strlen(delimiter->token)+1))
			break ;
		if (ft_strchr(line, '$'))
		{
			tmp = line;
			line = get_expanded_argv(line, list, status);
			free(tmp);
		}
		buf = ft_strjoinendl(buf, line);
		free(line);
	}
	return (buf);
}
void	put_heredoc_error(char *delimiter,t_tool *tool)
{
		if (tool->filename)
	{
		ft_printf_fd(2,"%s: line %d:",tool->filename,tool->line_count);
	}
	else
		ft_putstr_fd("minishell: ",2);
	ft_printf_fd(2,"warning: here-document delimited by end-of-file (wanted `%s')\n",delimiter);
}