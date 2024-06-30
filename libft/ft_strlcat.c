/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktsukamo <ktsukamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 22:52:03 by ktsukamo          #+#    #+#             */
/*   Updated: 2024/04/21 17:38:25 by ktsukamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	len_src;
	size_t	len_dst;

	if (!dstsize)
		return (ft_strlen(src));
	len_src = ft_strlen(src);
	len_dst = ft_strlen(dst);
	i = 0;
	if (dst)
	{
		if (len_dst >= dstsize)
			return (dstsize + len_src);
		while (src[i] && len_dst + i < dstsize - 1)
		{
			dst[len_dst + i] = src[i];
			i++;
		}
		dst[len_dst + i] = '\0';
	}
	return (len_dst + len_src);
}

// size_t	my_strlen(const char *str)
// {
// 	size_t	length;

// 	length = 0;
// 	while (*str)
// 	{
// 		length++;
// 		str++;
// 	}
// 	return (length);
// }

// #include <stdio.h>

// int	main(void)
// {
// 	char	*dst1;
// 	char	*dst2;
// 	char	*src1;
// 	char	*src2;

// 	dst1 = calloc(100, sizeof(char));
// 	dst2 = calloc(100, sizeof(char));
// 	src1 = calloc(100, sizeof(char));
// 	src2 = calloc(100, sizeof(char));
// 	for (int i = 0; i < 99; i++)
// 	{
// 		src1[i] = i + 1;
// 		src2[i] = i + 1;
// 	}
// 	printf("%lu", ft_strlcat(NULL, src2, 0));
// 	printf("%lu", strlcat(NULL, src2, 0));
// }
