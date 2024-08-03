/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktsukamo <ktsukamo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 20:45:33 by ktsukamo          #+#    #+#             */
/*   Updated: 2024/08/03 20:53:17 by ktsukamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	expand_file(t_token **ptr, t_tool *tool, t_var **list)
{
	char	*file;
	int		fd;

	file = NULL;
	file = get_expanded_argv((*ptr)->token, list, &tool->status);
	if (file[0] == '\0')
	{
		put_error_message((*ptr)->token, "ambiguous redirect", tool);
		(*ptr) = (*ptr)->next;
		free(file);
		return (FILE_ERROR);
	}
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		put_error_message(file, NULL, tool);
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

void	redirect_close_and_dup(int *pipefd)
{
	waitpid(-1, NULL, 0);
	if (close(pipefd[1]) == -1)
		fatal_error("close");
	if (dup2(pipefd[0], STDIN_FILENO) == -1)
		fatal_error("dup2");
	if (close(pipefd[0]) == -1)
		fatal_error("close");
}
