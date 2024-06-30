/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   12_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktsukamo <ktsukamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 17:20:46 by motttyam          #+#    #+#             */
/*   Updated: 2024/04/15 22:20:17 by ktsukamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		c -= 32;
	return (c);
}

// #include <ctype.h>
// #include <stdio.h>

// int	main(void)
// {
// 	printf("me: %d ans: %d\n", ft_toupper('a'), toupper('a'));
// 	printf("me: %d ans: %d\n", ft_toupper('A'), toupper('A'));
// 	// printf("me: %d ans: %d", ft_toupper(''), toupper(''));
// 	printf("me: %d ans: %d\n", ft_toupper('1'), toupper('1'));
// 	printf("me: %d ans: %d\n", ft_toupper('\n'), toupper('\n'));
// 	printf("me: %d ans: %d\n", ft_toupper('+'), toupper('+'));
// }