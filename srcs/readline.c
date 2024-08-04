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

char	*rl_input(t_tool *tool, t_var **list)
{
	char	*line;

	tool->ps1 = ft_getenv(list, "PS1");
	tool->ps2 = ft_getenv(list, "PS2");
	rl_outstream = stderr;
	line = NULL;
	if (tool->ps1)
		line = readline(tool->ps1);
	else
		line = readline(PROMPT);
	if (!line)
		return (NULL);
	if (*line)
		add_history(line);
	return (line);
}
