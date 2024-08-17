/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyoshimi <nyoshimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 22:31:54 by ktsukamo          #+#    #+#             */
/*   Updated: 2024/08/18 01:06:55 by nyoshimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	redirect(t_token **ptr, t_tool *tool, t_parser *parser)
{
	int	flag;

	flag = 0;
	if (parser->redirect_flag == FILE_ERROR)
	{
		(*ptr) = (*ptr)->next->next;
		return(FILE_ERROR);
	}
	if ((*ptr)->type == INPUT_REDIRECTION)
	{
		flag = input_redirect(ptr, tool, parser->list);
	}
	else if ((*ptr)->type == HEREDOCUMENT)
	{
		(*ptr) = (*ptr)->next;
		save_heredoc((*ptr));
		(*ptr) = (*ptr)->next;
	}
	else if ((*ptr)->type == OUTPUT_REDIRECTION)
	{
		flag = output_redirect(ptr, tool, parser->list);
	}
	else if ((*ptr)->type == OUTPUT_APPENDING)
	{
		flag = output_append(ptr, tool, parser->list);
	}
	else
		fatal_error("no redirection");
	return (flag);
}

int	input_redirect(t_token **ptr, t_tool *tool, t_var **list)
{
	int	fd;

	(*ptr) = (*ptr)->next;
	if ((*ptr)->type == WORD_EXPANDED || (*ptr)->type == QUOTE_EXPANDED)
		return (expand_file(ptr, tool, list));
	fd = open((*ptr)->token, O_RDONLY);
	if (fd == -1)
	{
		put_error_message((*ptr)->token, NULL, tool);
		(*ptr) = (*ptr)->next;
		return (FILE_ERROR);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	(*ptr) = (*ptr)->next;
	return (PIPE_AND_EXECVE);
}

int	save_heredoc(t_token *input)
{
	int		pipefd[2];
	pid_t	pid;

	if (pipe(pipefd) == -1)
		fatal_error("pipe");
	pid = fork();
	if (pid == -1)
		fatal_error("fork");
	if (pid == 0)
	{
		if (close(pipefd[0]) == -1)
			fatal_error("close");
		write(pipefd[1], input->token, ft_strlen(input->token));
		exit(0);
	}
	else
		redirect_close_and_dup(pipefd);
	return (0);
}

int	output_redirect(t_token **ptr, t_tool *tool, t_var **list)
{
	int	fd;

	(*ptr) = (*ptr)->next;
	if ((*ptr)->type == WORD_EXPANDED || (*ptr)->type == QUOTE_EXPANDED)
		return (expand_file(ptr, tool, list));
	fd = open((*ptr)->token, O_WRONLY | O_TRUNC);
	if (fd == -1)
	{
		if (errno == EACCES)
		{
			put_error_message((*ptr)->token, NULL, tool);
			(*ptr) = (*ptr)->next;
			return (FILE_ERROR);
		}
		fd = open((*ptr)->token, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
	}
	(*ptr) = (*ptr)->next;
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (EXECVE_ONLY);
}

int	output_append(t_token **ptr, t_tool *tool, t_var **list)
{
	int	fd;

	(*ptr) = (*ptr)->next;
	if ((*ptr)->type == WORD_EXPANDED || (*ptr)->type == QUOTE_EXPANDED)
		return (expand_file(ptr, tool, list));
	fd = open((*ptr)->token, O_WRONLY | O_APPEND);
	if (fd == -1)
	{
		if (errno == EACCES)
		{
			put_error_message((*ptr)->token, NULL, tool);
			(*ptr) = (*ptr)->next;
			return (FILE_ERROR);
		}
		fd = open((*ptr)->token, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
	}
	(*ptr) = (*ptr)->next;
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (EXECVE_ONLY);
}
