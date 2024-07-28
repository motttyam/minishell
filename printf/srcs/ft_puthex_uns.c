/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex_uns.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktsukamo <ktsukamo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 21:22:38 by ktsukamo          #+#    #+#             */
/*   Updated: 2024/07/28 18:01:13 by ktsukamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int	ft_puthex_uns(unsigned long int num, int fd)
{
	int	count;

	count = 0;
	count += 2;
	write(1, "0x", 2);
	ft_puthex_uns_recursive(num, &count, fd);
	return (count + 1);
}

void	ft_puthex_uns_recursive(unsigned long int num, int *count, int fd)
{
	char c;
	if (num >= 16)
	{
		ft_puthex_uns_recursive(num / 16, count, fd);
		(*count)++;
	}
	if (num % 16 <= 9)
	{
		c = (num % 16) + '0';
		write(fd, &c, 1);
	}
	else if (num % 16 > 9)
	{
		c = (num % 16) - 10 + 'a';
		write(fd, &c, 1);
	}
}