/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktsukamo <ktsukamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 13:32:26 by motttyam          #+#    #+#             */
/*   Updated: 2024/04/15 22:19:26 by ktsukamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

int	ft_isprint(int c)
{
	if (c >= ' ' && c <= '~')
		return (1);
	else
		return (0);
}

// #include <ctype.h>
// #include <stdio.h>

// int	main(void)
// {
// 	printf("me: %d ans: %d\n", ft_isprint('a'),   isprint('a'));
// 	printf("me: %d ans: %d\n", ft_isprint('A'),   isprint('A'));
// 	// printf("me: %d ans: %d", ft_  isprint(''),   isprint(''));
// 	printf("me: %d ans: %d\n", ft_isprint('1'),   isprint('1'));
// 	printf("me: %d ans: %d\n", ft_isprint('\n'),   isprint('\n'));
// 	printf("me: %d ans: %d\n", ft_isprint('+'),   isprint('+'));
// }