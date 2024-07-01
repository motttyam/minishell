/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyoshimi <nyoshimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 17:24:32 by nyoshimi          #+#    #+#             */
/*   Updated: 2024/06/23 17:26:28 by nyoshimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	recursive_readline(void)
{
	char			*line;
	t_token_lexer	lexer;
	t_token			*l;

	rl_outstream = stderr;
	while (1)
	{
		line = readline(PROMPT);
		if (!line)
			break ;
		if (*line)
			add_history(line);
		lex_token(&lexer, line);
		/*tokenの確認*/
		l = lexer.first;
		while (l)
		{
			printf("token = %s\n", l->token);
			l = l->next;
		}
		free(line);
	}
	exit(0);
}

// void recursive_readline(void)
// {
// 	char *line;
// 	t_token_lexer lexer;

// 	rl_outstream =  stderr;
// 	line = readline(PROMPT);
// 	add_history(line);
// 	lex_token(&lexer,line);
// 	/*tokenの確認*/
// 	t_token *l;
// 	l = lexer.first;
// 	while(l)
// 	{
// 		printf("token = %s\n",l->token);
// 		l = l->next;
// 	}
// 	if (!ft_strncmp(line, "exit", 4)) //終了条件はのちに修正必須(exitの実装やシグナル)
// 	{
// 		free(line);
// 		exit(1);
// 	}
// 	free(line);
// 	recursive_readline();
// }