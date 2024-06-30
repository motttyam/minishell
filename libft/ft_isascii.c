/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktsukamo <ktsukamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 13:26:48 by motttyam          #+#    #+#             */
/*   Updated: 2024/04/15 22:18:33 by ktsukamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
	{
		return (1);
	}
	else
		return (0);
}

// #include <ctype.h>
// #include <stdio.h>

// int	main(void)
// {
// 	printf("me: %d ans: %d\n", ft_isascii('a'),  isascii('a'));
// 	printf("me: %d ans: %d\n", ft_isascii('A'),  isascii('A'));
// 	// printf("me: %d ans: %d", ft_ isascii(''),  isascii(''));
// 	printf("me: %d ans: %d\n", ft_isascii('1'),  isascii('1'));
// 	printf("me: %d ans: %d\n", ft_isascii('\n'),  isascii('\n'));
// 	printf("me: %d ans: %d\n", ft_isascii('+'),  isascii('+'));
// }