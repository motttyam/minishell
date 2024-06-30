/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   15_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktsukamo <ktsukamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 23:10:36 by motttyam          #+#    #+#             */
/*   Updated: 2024/04/19 23:07:18 by ktsukamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;
	int	length;

	i = 1;
	length = (int)ft_strlen(s);
	while (i < length + 1)
	{
		if (s[length - i] == (char)c)
			return ((char *)(s + length - i));
		i++;
	}
	if (c == '\0')
		return ((char *)(s + length));
	return (0);
}

// #include <stdio.h>
// #include <string.h> // strrchr関数を使用するために必要

// char *ft_strrchr(const char *s, int c); // あなたの関数のプロトタイプ宣言

// void test_strrchr(const char *string, int character) {
//     char *result1 = strrchr(string, character);
//     char *result2 = ft_strrchr(string, character);

//     printf("Testing: %s, Char: %c\n", string, (char)character);
//     printf("strrchr: %s\n", result1 ? result1 : "NULL");
//     printf("ft_strrchr: %s\n", result2 ? result2 : "NULL");
//     printf("%s\n", (result1 == result2) ? "SUCCESS" : "FAIL");
// }

// int main(void) {
//     // 検索対象の文字が文字列の末尾にある場合
//     test_strrchr("Hello, World!", '!');
//     // 検索対象の文字が文字列の先頭にある場合
//     test_strrchr("Hello, World! Hello, Universe!", 'H');
//     // 検索対象の文字が文字列中に複数存在する場合
//     test_strrchr("Hello, World! Hello, Universe!", 'o');
//     // 検索対象の文字が文字列に存在しない場合
//     test_strrchr("Hello, World!", 'x');
//     // 文字列が空の場合
//     test_strrchr("", 'H');
//     // 検索対象の文字がヌル文字 ('\0') の場合
//     test_strrchr("Hello, World!", '\0');

//     return (0);
// }
