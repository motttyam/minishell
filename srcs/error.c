/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktsukamo <ktsukamo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 23:12:26 by nyoshimi          #+#    #+#             */
/*   Updated: 2024/07/14 20:03:05 by ktsukamo         ###   ########.fr       */
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
	ft_putendl_fd("Quotation mark not closed.",2);
	exit(1);
}

void put_error_message(char *argv, int flag)
{
	write(2, "minishell: ", 11);
	write(2, argv, ft_strlen(argv));
	write(2, ": ", 2);
	if (flag == 1)
		write(2, "command not found\n", 10);
	else
		perror("");
}