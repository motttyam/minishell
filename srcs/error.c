/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyoshimi <nyoshimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 23:12:26 by nyoshimi          #+#    #+#             */
/*   Updated: 2024/07/24 21:50:45 by nyoshimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	fatal_error(const char *msg)
{
	dprintf(2, "Fatal Error: %s\n", msg);
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

void	put_error_message(char *argv, char *message)
{
	ft_putstr_fd("minishell: ",2);
	ft_putstr_fd(argv,2);
	ft_putstr_fd(": ",2);
	if (message)
		ft_putendl_fd(message,2);
	else
		perror("");
}