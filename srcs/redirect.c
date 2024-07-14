/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktsukamo <ktsukamo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 22:31:54 by ktsukamo          #+#    #+#             */
/*   Updated: 2024/07/14 22:18:20 by ktsukamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int		input_redirect(t_token **ptr);
// int	heredoc(t_token **ptr);
int		output_redirect(t_token **ptr);
int		output_append(t_token **ptr);

int	redirect(t_token **ptr)
{
	int	flag;

	flag = 0;
	if ((*ptr)->type == INPUT_REDIRECTION)
	{
		flag = input_redirect(ptr);
	}
	// if ((*ptr)->type == HEREDOCUMENT)
	// {
	// 	heredoc(ptr);
	// }
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
		put_error_message((*ptr)->token, 0);
		(*ptr) = (*ptr)->next;
		return (-1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	(*ptr) = (*ptr)->next;
	return (0);
}

// void	heredoc(ptr)
// {
// 	return ;
// }

int	output_redirect(t_token **ptr)
{
	int	fd;

	(*ptr) = (*ptr)->next;
	fd = open((*ptr)->token, O_WRONLY | O_TRUNC);
	if (fd == -1)
	{
		if (errno == EACCES)
		{
			put_error_message((*ptr)->token, 0);
			return (-1);
		}
		fd = open((*ptr)->token, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
	}
	(*ptr) = (*ptr)->next;
	dup2(fd, STDOUT_FILENO);
	close(fd);
	fprintf(stderr, "flag: %d\n", 0);
	return (0);
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
			put_error_message((*ptr)->token, 0);
			return (-1);
		}
		fd = open((*ptr)->token, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
	}
	(*ptr) = (*ptr)->next;
	dup2(fd, STDOUT_FILENO);
	close(fd);
	fprintf(stderr, "flag: %d\n", 0);
	return (0);
}
