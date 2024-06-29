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

#include "minishell.h"

int	ft_strcmp(char *str1, char *str2)
{
	size_t	i;
	int		num;

	i = 0;
	num = 0;
	if (!str1 || !str2)
		return (0);
	while (str1[i] && str2[i])
	{
		num = (unsigned char)str1[i] - (unsigned char)str2[i];
		if (str1[i] != str2[i])
			break ;
		i++;
	}
	num = (unsigned char)str1[i] - (unsigned char)str2[i];
	return (num);
}

void recursive_readline(void)
{
	char *line;
	t_token_lexer lexer;

	line = readline(PROMPT);
	add_history(line);
	lex_token(&lexer,line);
	/*tokenの確認*/
	t_token *l;
	l = lexer.first;
	while(l)
	{
		printf("token = %s\n",l->token);
		l = l->next;
	}
	if (!ft_strcmp(line,"exit")) //終了条件はのちに修正必須(exitの実装やシグナル)
	{
		free(line);
		exit(1);
	}
	free(line);
	recursive_readline();
}