/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_uns_fd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktsukamo <ktsukamo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 20:49:03 by ktsukamo          #+#    #+#             */
/*   Updated: 2024/07/28 17:59:51 by ktsukamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

void	putnbr_uns_recursive(unsigned int n, int fd, int *count)
{
	char	c;
	if (n >= 10)
	{
		(*count)++;
		putnbr_uns_recursive(n / 10, fd, count);
	}
	c = (n % 10) + '0';
	write(fd, &c, 1);
}

int	ft_putnbr_uns_fd(unsigned int n, int fd)
{
	int	count;
	
	count = 0;
	putnbr_uns_recursive(n, fd, &count);
	return (count + 1);
}
