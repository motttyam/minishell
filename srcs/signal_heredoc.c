/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktsukamo <ktsukamo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 13:46:01 by ktsukamo          #+#    #+#             */
/*   Updated: 2024/08/17 14:53:01 by ktsukamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	handle_heredoc(int signal)
{
	if (signal == SIGINT)
	{
		g_sig = SIGINT;
		ft_printf_fd(1, "\n");
		save_sig_status(SIG_HEREDOC);
		close(STDIN_FILENO);
	}
	if (signal == SIGQUIT)
		return ;
}

void	heredoc_signal_handler(void)
{
	signal(SIGINT, handle_heredoc);
	signal(SIGQUIT, handle_heredoc);
}

void	handle_execve(int signal)
{
	if (signal == SIGINT)
	{
		ft_printf_fd(1, "\n");
	}
	else if (signal == SIGQUIT)
	{
		ft_printf_fd(2, "Quit (core dumped)\n");
		save_sig_status(SIG_CHILD_QUIT);
	}
}

void	execve_signal_handler(void)
{
	signal(SIGINT, handle_execve);
	signal(SIGQUIT, handle_execve);
}

void default_signal_handler(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
