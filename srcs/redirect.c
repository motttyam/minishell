/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyoshimi <nyoshimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 22:31:54 by ktsukamo          #+#    #+#             */
/*   Updated: 2024/08/01 13:45:33 by nyoshimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	input_redirect(t_token **ptr,t_tool *tool,t_var **list);
int	save_heredoc(t_token *input);
int	output_redirect(t_token **ptr,t_tool *tool,t_var **list);
int	output_append(t_token **ptr,t_tool *tool,t_var **list);

int	redirect(t_token **ptr,t_tool *tool,t_parser *parser)
{
	int	flag;

	flag = 0;
	if ((*ptr)->type == INPUT_REDIRECTION)
	{
		flag = input_redirect(ptr,tool,parser->list);
	}
	else if ((*ptr)->type == HEREDOCUMENT)
	{
		(*ptr) = (*ptr)->next;
		save_heredoc((*ptr));
		(*ptr) = (*ptr)->next;
	}
	else if ((*ptr)->type == OUTPUT_REDIRECTION)
	{
		flag = output_redirect(ptr,tool,parser->list);
	}
	else if ((*ptr)->type == OUTPUT_APPENDING)
	{
		flag = output_append(ptr,tool,parser->list);
	}
	else
		fatal_error("予期しないエラー: redirectではない");
	return (flag);
}
int	expand_file(t_token **ptr,t_tool *tool,t_var **list)
{
	char	*file;
	int		fd;

	file = NULL;
	file = get_expanded_argv((*ptr)->token,list,&tool->status);
	if(file[0] == '\0')
	{
		put_error_message((*ptr)->token,"ambiguous redirect",tool);
		(*ptr) = (*ptr)->next;
		free(file);
		return (FILE_ERROR);
	}
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		put_error_message(file, NULL,tool);
		(*ptr) = (*ptr)->next;
		free(file);
		return (FILE_ERROR);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	(*ptr) = (*ptr)->next;
	free(file);
	return (PIPE_AND_EXECVE);
	
}

int	input_redirect(t_token **ptr,t_tool *tool,t_var **list)
{
	int	fd;

	(*ptr) = (*ptr)->next;
	if ((*ptr)->type == WORD_EXPANDED || (*ptr)->type == QUOTE_EXPANDED)
		return(expand_file(ptr,tool,list));
	fd = open((*ptr)->token, O_RDONLY);
	if (fd == -1)
	{
		put_error_message((*ptr)->token, NULL,tool);
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

int	output_redirect(t_token **ptr,t_tool *tool,t_var **list)
{
	int	fd;

	(*ptr) = (*ptr)->next;
	if ((*ptr)->type == WORD_EXPANDED || (*ptr)->type == QUOTE_EXPANDED)
		return(expand_file(ptr,tool,list));
	fd = open((*ptr)->token, O_WRONLY | O_TRUNC);
	if (fd == -1)
	{
		if (errno == EACCES)
		{
			put_error_message((*ptr)->token, NULL,tool);
			return (FILE_ERROR);
		}
		fd = open((*ptr)->token, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
	}
	(*ptr) = (*ptr)->next;
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (EXECVE_ONLY);
}

int	output_append(t_token **ptr,t_tool *tool,t_var **list)
{
	int	fd;

	(*ptr) = (*ptr)->next;
	if ((*ptr)->type == WORD_EXPANDED || (*ptr)->type == QUOTE_EXPANDED)
		return(expand_file(ptr,tool,list));
	fd = open((*ptr)->token, O_WRONLY | O_APPEND);
	if (fd == -1)
	{
		if (errno == EACCES)
		{
			put_error_message((*ptr)->token, NULL,tool);
			return (FILE_ERROR);
		}
		fd = open((*ptr)->token, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
	}
	(*ptr) = (*ptr)->next;
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (EXECVE_ONLY);
}
