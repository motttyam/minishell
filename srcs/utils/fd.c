/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktsukamo <ktsukamo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 13:55:52 by ktsukamo          #+#    #+#             */
/*   Updated: 2024/08/03 20:09:52 by ktsukamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	save_fd(t_fd *saved_fd)
{
	saved_fd->saved_stdin = dup(STDIN_FILENO);
	saved_fd->saved_stdout = dup(STDOUT_FILENO);
	saved_fd->saved_stderr = dup(STDERR_FILENO);
}

void	reinit_fd(t_fd saved_fd)
{
	dup2(saved_fd.saved_stdin, STDIN_FILENO);
	dup2(saved_fd.saved_stdout, STDOUT_FILENO);
	dup2(saved_fd.saved_stderr, STDERR_FILENO);
}

void	close_fd(t_fd saved_fd)
{
	close(saved_fd.saved_stdin);
	close(saved_fd.saved_stdout);
	close(saved_fd.saved_stderr);
}
