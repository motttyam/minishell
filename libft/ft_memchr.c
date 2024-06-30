/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   17_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktsukamo <ktsukamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 23:26:13 by motttyam          #+#    #+#             */
/*   Updated: 2024/04/15 22:20:44 by ktsukamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*ptr;

	i = 0;
	ptr = (unsigned char *)s;
	while (i < n)
	{
		if (ptr[i] == (unsigned char)c)
			return ((void *)(s + i));
		i++;
	}
	return (NULL);
}

// #include <stdio.h>
// #include <string.h>

// // あなたのft_memchr関数のプロトタイプ宣言
// void	*ft_memchr(const void *s, int c, size_t n);

// void	test_ft_memchr(const void *buffer, int c, size_t n)
// {
// 	const unsigned char	*result1 = ft_memchr(buffer, c, n);

// 	const unsigned char *result2 = memchr(buffer, c, n); // 標準のmemchr関数を使う
// 	printf("Testing ft_memchr with byte '%c' in first %zu bytes.\n", (char)c,
// 		n);
// 	printf("ft_memchr result: ");
// 	if (result1 != NULL)
// 	{
// 		printf("Found '%c' at position %ld.\n", (char)c, (long)(result1
// 				- (const unsigned char *)buffer));
// 	}
// 	else
// 	{
// 		printf("Byte '%c' not found.\n", (char)c);
// 	}
// 	printf("Standard memchr result: ");
// 	if (result2 != NULL)
// 	{
// 		printf("Found '%c' at position %ld.\n", (char)c, (long)(result2
// 				- (const unsigned char *)buffer));
// 	}
// 	else
// 	{
// 		printf("Byte '%c' not found.\n", (char)c);
// 	}
// 	if (result1 == result2)
// 	{
// 		printf("SUCCESS: Both results match.\n\n");
// 	}
// 	else
// 	{
// 		printf("FAIL: Results differ.\n\n");
// 	}
// }

// int	main(void)
// {
// 	const char	buffer[] = "Hello, world!";

// 	// 検索対象のバイトが配列の先頭にある場合
// 	test_ft_memchr(buffer, 'H', sizeof(buffer));
// 	// 検索対象のバイトが配列の中間にある場合
// 	test_ft_memchr(buffer, 'w', sizeof(buffer));
// 	// 検索対象のバイトが配列の末尾にある場合（この場合、ヌル終端文字）
// 	test_ft_memchr(buffer, '\0', sizeof(buffer));
// 	// 検索対象が見つからない場合
// 	test_ft_memchr(buffer, 'x', sizeof(buffer));
// 	// 検索対象が配列の先頭にあるが、検索範囲が0の場合
// 	test_ft_memchr(buffer, 'H', 0);
// 	return (0);
// }
