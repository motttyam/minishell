/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktsukamo <ktsukamo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 17:06:27 by nyoshimi          #+#    #+#             */
/*   Updated: 2024/07/17 23:07:15 by ktsukamo         ###   ########.fr       */
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

void close_fd(t_fd saved_fd)
{
	close(saved_fd.saved_stdin);
	close(saved_fd.saved_stdout);
	close(saved_fd.saved_stderr);
}

void hogehoge(t_var *tmp)
{
	while (tmp)
	{
		fprintf(stderr, "key: %s\nvalue: %s\n\n", tmp->key,tmp->value);
		tmp = tmp->next;
	}
}

int	main(void)
{
	t_var 			**varlist;
	char			*input;
	t_token_lexer	lexer;
	t_fd			saved_fd;

	save_fd(&saved_fd);
	get_envlist(varlist);

	// // test for varlist

	while (1)
	{
		input = NULL;
		input = rl_input();
		if (!input)
			break ;
		lex_token(&lexer, input);
		parse_token(lexer.first, saved_fd, varlist);
		reinit_fd(saved_fd);
	}
	close_fd(saved_fd);
	ft_putendl_fd("exit", 2);
	return (0);
}

// t_token *l; // テスト用である理解をしている
// /*tokenの確認*/
// l = lexer.first;
// int i = 1;
// while (l)
// {
// 	printf("token%d = {%s,type%d}\n",i, l->token, l->type);
// 	l = l->next;
// 	i++;
// }