/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktsukamo <ktsukamo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 17:06:27 by nyoshimi          #+#    #+#             */
/*   Updated: 2024/07/07 15:22:59 by ktsukamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(void)
{
	char			*input;
	t_token_lexer	lexer;

	t_token *l; // テスト用である理解をしている
	while (1)
	{
		input = NULL;
		input = rl_input();
		if (!input)
			break ;
		lex_token(&lexer, input);
		/*tokenの確認*/
		l = lexer.first;
		while (l)
		{
			printf("token = %s\n", l->token);
			l = l->next;
		}
	}
	ft_putendl_fd("exit", 2);
	return (0);
}
