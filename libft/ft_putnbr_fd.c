/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   33_ft_putnbr_fd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktsukamo <ktsukamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 20:10:27 by motttyam          #+#    #+#             */
/*   Updated: 2024/04/15 22:43:03 by ktsukamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

void	put_recursive(int n, int fd)
{
	char	c;

	if (n >= 10)
		put_recursive(n / 10, fd);
	c = (n % 10) + '0';
	write(fd, &c, 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	if (n < 0)
	{
		write(fd, "-", 1);
		n = -n;
	}
	put_recursive(n, fd);
}

// int main (void)
// {
// 	ft_putnbr_fd(-123456789, 1);
// 	return (0);
// }
