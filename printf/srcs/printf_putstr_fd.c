/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_putstr_fd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktsukamo <ktsukamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 17:11:19 by ktsukamo          #+#    #+#             */
/*   Updated: 2024/06/23 22:01:49 by ktsukamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int	printf_putstr_fd(char *s, int fd)
{
	size_t	length;
	size_t	already_written;
	size_t	write_to_byte;

	if (!s)
	{
		write(fd, "(null)" , 6);
		return (6);
	}
	length = printf_strlen(s);
	already_written = 0;
	write_to_byte = 0;
	while (length > write_to_byte)
	{
		write_to_byte = length - already_written;
		if (write_to_byte > INT_MAX)
		{
			write(fd, s + already_written, 10);
		}
		else
			write(fd, s + already_written, write_to_byte);
	}
	return (length);
}
