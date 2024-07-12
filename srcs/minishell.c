/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktsukamo <ktsukamo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 17:06:27 by nyoshimi          #+#    #+#             */
/*   Updated: 2024/07/12 22:30:16 by ktsukamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(void)
{
	char			*input;
	t_token_lexer	lexer;
	int				saved_stdin;

	saved_stdin = dup(STDIN_FILENO);
	// t_token *l; // テスト用である理解をしている
	while (1)
	{
		input = NULL;
		input = rl_input();
		if (!input)
			break ;
		// input = search_path((const char *)input);
		lex_token(&lexer, input);
		parse_token(lexer.first);
		dup2(saved_stdin, STDIN_FILENO);
		close(saved_stdin);
		// /*tokenの確認*/
		// l = lexer.first;
		// int i = 1;
		// while (l)
		// {
		// 	printf("token%d = {%s,type%d}\n",i, l->token, l->type);
		// 	l = l->next;
		// 	i++;
		// }
	}
	ft_putendl_fd("exit", 2);
	return (0);
}
