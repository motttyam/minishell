/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   28_ft_strmapi.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktsukamo <ktsukamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 14:03:50 by motttyam          #+#    #+#             */
/*   Updated: 2024/04/15 22:41:14 by ktsukamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*result;
	int		i;

	if (!s || !f)
		return (NULL);
	result = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!result)
		return (NULL);
	i = 0;
	while (s[i])
	{
		result[i] = f(i, s[i]);
		i++;
	}
	result[i] = '\0';
	return (result);
}

// #include <stdio.h>
// #include <ctype.h>

// // テスト用の関数：文字を大文字に変換
// char to_upper(unsigned int i, char c) {
//     (void)i; // この例ではインデックスは使用しない
//     return (toupper(c));
// }

// // テスト用の関数：インデックスが奇数の場合に'*'に置き換える
// char odd_to_star(unsigned int i, char c) {
//     if (i % 2 == 1) return ('*');
//     return (c);
// }

// // `strmapi`関数のテストを行う
// void test_strmapi() {
//     char const *s = "hello, world!";

//     char *upper_result = ft_strmapi(s, to_upper);
//     printf("Upper case: %s\n", upper_result);
//     free(upper_result); // 動的に割り当てたメモリを解放

//     char *odd_result = ft_strmapi(s, odd_to_star);
//     printf("Odd to '*': %s\n", odd_result);
//     free(odd_result); // 動的に割り当てたメモリを解放
// }

// int main() {
//     test_strmapi();
//     return (0);
// }
