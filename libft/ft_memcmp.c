/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   18_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktsukamo <ktsukamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 23:46:22 by motttyam          #+#    #+#             */
/*   Updated: 2024/04/15 22:20:48 by ktsukamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*p1;
	unsigned char	*p2;
	size_t			i;

	p1 = (unsigned char *)s1;
	p2 = (unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (p1[i] != p2[i])
			return (p1[i] - p2[i]);
		i++;
	}
	return (0);
}

// #include <stdio.h>
// #include <string.h>

// // あなたのft_memcmp関数のプロトタイプ宣言
// int ft_memcmp(const void *s1, const void *s2, size_t n);

// void test_ft_memcmp(const void *s1, const void *s2, size_t n) {
//     int result1 = ft_memcmp(s1, s2, n);
//     int result2 = memcmp(s1, s2, n);

//     printf("Testing ft_memcmp with n = %zu.\n", n);
//     printf("ft_memcmp result: %d\n", result1);
//     printf("memcmp result: %d\n", result2);

//     if ((result1 == 0 && result2 == 0) || (result1 < 0 && result2 < 0)
	// || (result1 > 0 && result2 > 0)) {
//         printf("SUCCESS: Both results match.\n\n");
//     } else {
//         printf("FAIL: Results differ.\n\n");
//     }
// }

// int main(void) {
//     const char str1[] = "Hello, world!";
//     const char str2[] = "Hello, world!";
//     const char str3[] = "Hello, World!";

//     // 完全に一致する場合
//     test_ft_memcmp(str1, str2, sizeof(str1));

//     // 異なるバイトが含まれる場合
//     test_ft_memcmp(str1, str3, sizeof(str1));

//     // 比較するバイト数が0の場合
//     test_ft_memcmp(str1, str3, 0);

//     // 最初の数バイトが同じで後に異なる場合
//     test_ft_memcmp(str1, str3, 5);

//     // 大きなバイト値と小さなバイト値を比較
//     const unsigned char big[] = {255, 255, 255};
//     const unsigned char small[] = {0, 0, 0};
//     test_ft_memcmp(big, small, sizeof(big));

//     return (0);
// }
