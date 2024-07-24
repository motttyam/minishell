/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyoshimi <nyoshimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 22:31:54 by ktsukamo          #+#    #+#             */
/*   Updated: 2024/07/24 20:23:09 by nyoshimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	input_redirect(t_token **ptr);
int	heredoc(t_token **ptr);
int	save_heredoc(t_token *input);
int	output_redirect(t_token **ptr);
int	output_append(t_token **ptr);

int	redirect(t_token **ptr)
{
	int	flag;

	flag = 0;
	if ((*ptr)->type == INPUT_REDIRECTION)
	{
		flag = input_redirect(ptr);
	}
	else if ((*ptr)->type == HEREDOCUMENT)
	{
		(*ptr) = (*ptr)->next;
		save_heredoc((*ptr));
		(*ptr) = (*ptr)->next;
	}
	else if ((*ptr)->type == OUTPUT_REDIRECTION)
	{
		flag = output_redirect(ptr);
	}
	else if ((*ptr)->type == OUTPUT_APPENDING)
	{
		flag = output_append(ptr);
	}
	else
		fatal_error("予期しないエラー: redirectではない");
	return (flag);
}

int	input_redirect(t_token **ptr)
{
	int	fd;

	(*ptr) = (*ptr)->next;
	fd = open((*ptr)->token, O_RDONLY);
	if (fd == -1)
	{
		put_error_message((*ptr)->token, NULL);
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
	{
		waitpid(-1, NULL, 0);
		if (close(pipefd[1]) == -1)
			fatal_error("close");
		if (dup2(pipefd[0], STDIN_FILENO) == -1)
			fatal_error("dup2");
		if (close(pipefd[0]) == -1)
			fatal_error("close");
	}
	return (0);
}

int	output_redirect(t_token **ptr)
{
	int	fd;

	(*ptr) = (*ptr)->next;
	fd = open((*ptr)->token, O_WRONLY | O_TRUNC);
	if (fd == -1)
	{
		if (errno == EACCES)
		{
			put_error_message((*ptr)->token, NULL);
			return (FILE_ERROR);
		}
		fd = open((*ptr)->token, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
	}
	(*ptr) = (*ptr)->next;
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (EXECVE_ONLY);
}

int	output_append(t_token **ptr)
{
	int	fd;

	(*ptr) = (*ptr)->next;
	fd = open((*ptr)->token, O_WRONLY | O_APPEND);
	if (fd == -1)
	{
		if (errno == EACCES)
		{
			put_error_message((*ptr)->token, NULL);
			return (FILE_ERROR);
		}
		fd = open((*ptr)->token, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
	}
	(*ptr) = (*ptr)->next;
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (EXECVE_ONLY);
}
