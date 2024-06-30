/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktsukamo <ktsukamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 23:06:46 by motttyam          #+#    #+#             */
/*   Updated: 2024/04/21 17:11:08 by ktsukamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)(s + i));
		i++;
	}
	if (c == '\0')
		return ((char *)(s + i));
	return (NULL);
}

// #include <stdio.h>
// #include <string.h> // strchr関数を使用するために必要

// void test_strchr(const char *string, int character) {
//     char *result1 = strchr(string, character);
//     char *result2 = ft_strchr(string, character);

//     printf("Testing: %s, Char: %c\n", string, (char)character);
//     printf("strchr: %s\n", result1 ? result1 : "NULL");
//     printf("ft_strchr: %s\n", result2 ? result2 : "NULL");
//     printf("%s\n", (result1 == result2) ? "SUCCESS" : "FAIL");
// }

// int main(void) {
//     // 検索対象の文字が文字列の先頭にある場合
//     test_strchr("Hello, World!", 'H');
//     // 検索対象の文字が文字列の末尾にある場合
//     test_strchr("Hello, World!", '!');
//     // 検索対象の文字が文字列中に複数存在する場合
//     test_strchr("Hello, World! Hello, Universe!", 'o');
//     // 検索対象の文字が文字列に存在しない場合
//     test_strchr("Hello, World!", 'x');
//     // 文字列が空の場合
//     test_strchr("", 'H');
//     // 検索対象の文字がヌル文字 ('\0') の場合
//     test_strchr("Hello, World!", '\0');
//     // 検索対象の文字が文字列の末尾にある場合（ヌル文字を含む）
//     test_strchr("Hello", '\0');

//     return (0);
// }
