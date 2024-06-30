/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktsukamo <ktsukamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 14:34:58 by motttyam          #+#    #+#             */
/*   Updated: 2024/04/21 17:18:44 by ktsukamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char		*ptr_dst;
	const unsigned char	*ptr_src;
	size_t				i;

	if (!dst && !src)
		return (NULL);
	ptr_dst = (unsigned char *)dst;
	ptr_src = (const unsigned char *)src;
	i = 0;
	while (i < n)
	{
		*ptr_dst++ = *ptr_src++;
		i++;
	}
	return (dst);
}

// #include <stdio.h>
// #include <string.h> // 標準のmemcpyのため

// // ft_memcpy関数のプロトタイプ宣言
// void *ft_memcpy(void *restrict dst, const void *restrict src, size_t n);

// int main(void)
// {
//     char src[10] = "Kazuki416";
//     char dst[10];
//     char dst2[10];

//     // 標準のmemcpyでdstをコピー
//     memcpy(dst, src, sizeof(src));

//     // カスタムft_memcpyでdst2をコピー
//     ft_memcpy(dst2, src, sizeof(src));

//     // 結果の出力
//     printf("Standard memcpy: %s\n", dst);
//     printf("Custom ft_memcpy: %s\n", dst2);

//     return (0);
// }
