/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktsukamo <ktsukamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 14:56:50 by motttyam          #+#    #+#             */
/*   Updated: 2024/04/20 19:10:39 by ktsukamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*p_dst;
	unsigned char	*p_src;
	size_t			i;

	p_dst = (unsigned char *)dst;
	p_src = (unsigned char *)src;
	if (dst == src)
		return (dst);
	if (p_dst > p_src && p_dst < p_src + len)
	{
		i = len - 1;
		while (i-- + 1 > 0)
			p_dst[i + 1] = p_src[i + 1];
	}
	else
	{
		i = 0;
		while (i < len)
		{
			p_dst[i] = p_src[i];
			i++;
		}
	}
	return (dst);
}

// #include <stdio.h>
// #include <string.h> // 標準のmemmove関数のため

// ここにft_memmove関数を定義またはインクルード

// void print_array(const char *tag, const unsigned char *arr, size_t len) {
//     printf("%s: ", tag);
//     for (size_t i = 0; i < len; i++) {
//         printf("%02x ", arr[i]);
//     }
//     printf("\n");
// }

// int main() {
//     unsigned char original[] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
// 0x08, 0x09, 0x0A};
//     size_t len = sizeof(original);
//     unsigned char test1[sizeof(original)];
//     unsigned char test2[sizeof(original)];

//     // オーバーラップしないコピーのテスト
//     memcpy(test1, original, len); // 初期化
//     ft_memmove(test1 + 2, test1, 5); // カスタム関数でオーバーラップしない部分をコピー
//     memmove(test2, original, len); // 初期化
//     memmove(test2 + 2, test2, 5); // 標準関数でオーバーラップしない部分をコピー
//     print_array("Non-overlapping ft_memmove", test1, len);
//     print_array("Non-overlapping memmove", test2, len);
// }