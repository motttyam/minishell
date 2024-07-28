/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktsukamo <ktsukamo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 21:22:38 by ktsukamo          #+#    #+#             */
/*   Updated: 2024/07/28 18:00:32 by ktsukamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

//memo 
// 4294967396
// 4294967196

int	ft_puthex(long int num, int flag, int fd)
{
	int	count;

	count = 0;
	if (flag == 1)
	{
		count += 2;
		write(1, "0x", 2);
	}
	if (num < 0)
		num = 4294967295 + num + 1;
	ft_puthex_recursive(num, &count, flag, fd);
	return (count);
}

void	ft_puthex_recursive(long int num, int *count, int flag, int fd)
{
	char c;
	if (num >= 16)
	{
		ft_puthex_recursive(num / 16, count, flag, fd);
	}
	if (num % 16 <= 9)
	{
		c = (num % 16) + '0';
		write(fd, &c, 1);
		(*count)++;
	}
	else if (num % 16 > 9 && flag != 0)
	{
		c = (num % 16) - 10 + 'a';
		write(fd, &c, 1);
		(*count)++;
	}
	else
	{
		c = (num % 16) - 10 + 'A';
		write(fd, &c, 1);
		(*count)++;
	}
}