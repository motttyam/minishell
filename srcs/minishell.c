/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktsukamo <ktsukamo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 17:06:27 by nyoshimi          #+#    #+#             */
/*   Updated: 2024/07/22 23:04:30 by ktsukamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

void	handle_signal(int signal)
{
	if (signal == SIGINT)
	{
		rl_on_new_line();
		write(STDOUT_FILENO, "\n", 1);
		// rl_replace_line("", 0);
		rl_redisplay();
	}
}

int	main(void)
{
	t_var			*first;
	char			*input;
	t_token_lexer	lexer;
	t_fd			saved_fd;

	signal(SIGINT, handle_signal);
	signal(SIGQUIT, SIG_IGN);
	save_fd(&saved_fd);
	first = NULL;
	get_envlist(&first);
	while (1)
	{
		input = NULL;
		input = rl_input();
		if (!input)
			break ;
		lex_token(&lexer, input);
		parse_token(lexer.first, saved_fd, &first);
		reinit_fd(saved_fd);
	}
	close_fd(saved_fd);
	ft_putendl_fd("exit", 2);
	return (0);
}
