/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyoshimi <nyoshimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 23:12:26 by nyoshimi          #+#    #+#             */
/*   Updated: 2024/08/01 08:21:51 by nyoshimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	fatal_error(const char *msg)
{
	ft_printf_fd(2, "Fatal Error: %s\n", msg);
	exit(1);
}

void	handle_malloc_error(void)
{
	perror("malloc failed");
	exit(1);
}

void	quote_error(void)
{
	ft_putendl_fd("Quotation mark not closed.", 2);
	exit(1);
}

void	put_error_message(char *argv, char *message,t_tool *tool)
{
	if (tool->filename)
	{
		ft_printf_fd(2,"%s: line %d:",tool->filename,tool->line_count);
	}
	else
		ft_putstr_fd("minishell: ",2);
	ft_printf_fd(2,"%s: ",argv);
	if (message)
		ft_putendl_fd(message,2);
	else
		perror("");
}