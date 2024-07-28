/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_putnbr_fd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktsukamo <ktsukamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 20:49:03 by ktsukamo          #+#    #+#             */
/*   Updated: 2024/06/23 22:07:41 by ktsukamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

void	printf_put_recursive(int n, int fd, int *count)
{
	char	c;

	if (n >= 10)
	{
		(*count)++;
		printf_put_recursive(n / 10, fd, count);
	}
	c = (n % 10) + '0';
	write(fd, &c, 1);
}

int	printf_putnbr_fd(int n, int fd)
{
	int	count;

	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return (11);
	}
	count = 0;
	if (n < 0)
	{
		write(fd, "-", 1);
		n = -n;
		count++;
	}
	printf_put_recursive(n, fd, &count);
	return (count + 1);
}
