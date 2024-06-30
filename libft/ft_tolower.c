/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   13_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktsukamo <ktsukamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 17:26:51 by motttyam          #+#    #+#             */
/*   Updated: 2024/04/15 22:20:21 by ktsukamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		c += 32;
	return (c);
}

// #include <ctype.h>
// #include <stdio.h>

// int	main(void)
// {
// 	printf("me: %d ans: %d\n", ft_tolower('a'), tolower('a'));
// 	printf("me: %d ans: %d\n", ft_tolower('A'), tolower('A'));
// 	// printf("me: %d ans: %d", ft_tolower(''), tolower(''));
// 	printf("me: %d ans: %d\n", ft_tolower('1'), tolower('1'));
// 	printf("me: %d ans: %d\n", ft_tolower('\n'), tolower('\n'));
// 	printf("me: %d ans: %d\n", ft_tolower('+'), tolower('+'));
// }