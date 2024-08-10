/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktsukamo <ktsukamo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 13:46:01 by ktsukamo          #+#    #+#             */
/*   Updated: 2024/08/10 16:32:48 by ktsukamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	handle_heredoc(int signal)
{
	if (signal == SIGINT)
	{
		g_sig = SIGINT;
		save_sig_status(SIG_HEREDOC);
		ft_printf_fd(1, "\n");
		close(STDIN_FILENO);
	}
}

void	heredoc_signal_handler(void)
{
	signal(SIGINT, handle_heredoc);
	signal(SIGQUIT, SIG_IGN);
}

int	save_sig_status(int flag)
{
	static int	i = 0;

	if (flag == SIG_NORMAL)
	{
		i = SIG_NORMAL;
		return (0);
	}
	else if (flag == SIG_HEREDOC)
	{
		i = SIG_HEREDOC;
		return (0);
	}
	else if (flag == -1)
	{
		return (i);
	}
	ft_printf_fd(2, "sig_status Error\nflag:%d\n", flag);
	return (-1);
}

void	handle_interactive(int signal)
{
	// interactive modeの signal
	if (signal == SIGINT)
	{
		g_sig = SIGINT;
		save_sig_status(SIG_NORMAL);
		rl_on_new_line();
		ft_printf_fd(1, "\n");
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	ignore_signal_handler(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	setup_signal_handler(void)
{
	signal(SIGINT, handle_interactive);
	signal(SIGQUIT, SIG_IGN);
}
