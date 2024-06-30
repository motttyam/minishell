/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktsukamo <ktsukamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 11:00:42 by ktsukamo          #+#    #+#             */
/*   Updated: 2024/04/21 18:19:50 by ktsukamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

int	ft_atoi(const char *str)
{
	long long	symbol;
	long long	num;

	num = 0;
	symbol = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			symbol = -symbol;
		str++;
	}
	if (symbol == 1)
		num = ft_is_overflow(str, 0);
	else if (symbol == -1)
		num = ft_is_underflow(str, 0);
	return ((int)num);
}

long long	ft_is_overflow(const char *str, long long num)
{
	while (*str >= '0' && *str <= '9')
	{
		if ((LONG_MAX - (*str - '0')) / 10 > num - 1)
		{
			num = num * 10 + (*str - '0');
			str++;
		}
		else
			return ((int)LONG_MAX);
	}
	return (num);
}

long long	ft_is_underflow(const char *str, long long num)
{
	while (*str >= '0' && *str <= '9')
	{
		if ((LONG_MAX - (*str - '0')) / 10 > num - 1)
		{
			num = num * 10 + (*str - '0');
			str++;
		}
		else
			return ((int)LONG_MIN);
	}
	return (-1 * num);
}
