/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   07_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktsukamo <ktsukamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 14:22:08 by motttyam          #+#    #+#             */
/*   Updated: 2024/04/15 22:19:37 by ktsukamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*ptr;
	size_t			i;

	ptr = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		ptr[i] = '\0';
		i++;
	}
	return ;
}

// #include <stdio.h>
// #include <strings.h> // POSIX標準のbzeroのため
// #include <string.h> // memcmpのため

// // ft_bzero関数の宣言（またはヘッダファイルのインクルード）
// void ft_bzero(void *s, size_t n);

// int main(void)
// {
//     char original[10];
//     char test[10];

//     // 標準のbzeroを使用
//     bzero(original, sizeof(original));

//     // カスタムft_bzeroを使用
//     ft_bzero(test, sizeof(test));

//     // 結果の比較
//     if (memcmp(original, test, sizeof(original)) == 0)
//     {
//         printf("Success: ft_bzero works correctly.\n");
//     }
//     else
//     {
//         printf("Failure: ft_bzero does not match bzero.\n");
//     }

//     return (0);
// }
