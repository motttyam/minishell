/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   06_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktsukamo <ktsukamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 13:39:11 by motttyam          #+#    #+#             */
/*   Updated: 2024/04/18 00:51:15 by ktsukamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*ptr;

	ptr = (unsigned char *)b;
	i = 0;
	while (i < len)
	{
		ptr[i] = (unsigned char)c;
		i++;
	}
	return (b);
}

// #include <stdio.h>
// #include <string.h>

// void	test_memset_functions(char *description, int fillValue, size_t size)
// {
// 	char	*custom;
// 	int		is_same;

// 	char *original = malloc(size + 1); // 動的メモリ確保
// 	custom = malloc(size + 1);
// 	memset(original, fillValue, size);
// 	original[size] = '\0';
// 	ft_memset(custom, fillValue, size);
// 	custom[size] = '\0';
// 	// 結果の確認
// 	is_same = 1;
// 	for (size_t i = 0; i < size; i++)
// 	{
// 		if (original[i] != custom[i])
// 		{
// 			is_same = 0;
// 			break ;
// 		}
// 	}
// 	printf("%s\n", description);
// 	printf("original: %s\ncustom: %s\n", original, custom);
// 	if (is_same)
// 		printf("The arrays are identical.\n\n");
// 	else
// 		printf("The arrays are not identical.\n\n");
// 	free(original); // 動的メモリ解放
// 	free(custom);
// }

// int	main(void)
// {
// 	// 標準テスト
// 	test_memset_functions("Standard test case with size 10 and fill value
// '#' (ASCII 35)",	'#', 10);
// 	// コーナーケース: 配列のサイズが0
// 	test_memset_functions("Corner case with size 0", '#', 0);
// 	// コーナーケース: ASCII範囲外の値
// 	test_memset_functions("Corner case with
// fill value 256 (outside ASCII range)", 256, 10);
// 	// コーナーケース: 非常に大きな配列サイズ
// 	test_memset_functions("Corner case with a very large array size",
//  '#', 100);
// 	// コーナーケース: 特殊文字を使用
// 	test_memset_functions("Corner case with a special character (ASCII 7,
// 		bell)", '\a', 10);
// 	return (0);
// }
