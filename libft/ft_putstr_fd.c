/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktsukamo <ktsukamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 17:11:19 by ktsukamo          #+#    #+#             */
/*   Updated: 2024/04/21 17:35:13 by ktsukamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	size_t	length;
	size_t	already_written;
	size_t	write_to_byte;

	if (!s)
		return ;
	length = ft_strlen(s);
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
}

// int main (void)
// {
// 	char stdout[] = "hello, 42!";
// 	char file[] = "Hello, Shinjuku!";
// 	int fd;

// 	fd = 1;
// 	ft_putstr_fd(stdout, fd);

// 	fd = open("test.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 	ft_putstr_fd(file, fd);
// 	return (0);
// }
