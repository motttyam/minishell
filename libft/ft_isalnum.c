/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktsukamo <ktsukamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 12:18:48 by motttyam          #+#    #+#             */
/*   Updated: 2024/04/15 22:18:18 by ktsukamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

int	ft_isalnum(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (1);
	else if (c >= 'a' && c <= 'z')
		return (1);
	else if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

// #include <ctype.h>
// #include <stdio.h>

// int	main(void)
// {
// 	printf("me: %d ans: %d\n", ft_isalnum('a'), isalnum('a'));
// 	printf("me: %d ans: %d\n", ft_isalnum('A'), isalnum('A'));
// 	// printf("me: %d ans: %d", ft_isalnum(''), isalnum(''));
// 	printf("me: %d ans: %d\n", ft_isalnum('1'), isalnum('1'));
// 	printf("me: %d ans: %d\n", ft_isalnum('\n'), isalnum('\n'));
// 	printf("me: %d ans: %d\n", ft_isalnum('+'), isalnum('+'));
// }