/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   25_ft_strtrim.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktsukamo <ktsukamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 21:51:05 by motttyam          #+#    #+#             */
/*   Updated: 2024/04/19 23:44:28 by ktsukamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*dest;
	int		start;
	int		end;
	char	*ptr;

	if (!s1)
		return (NULL);
	start = 0;
	end = (int)ft_strlen((char *)s1) - 1;
	while (is_set(s1[start], set) && s1[start])
		start++;
	while (is_set(s1[end], set) && end >= start)
		end--;
	dest = (char *)malloc(sizeof(char) * (end - start + 2));
	if (!dest)
		return (NULL);
	ptr = dest;
	while (start <= end)
		*(dest++) = s1[start++];
	*dest = '\0';
	return (ptr);
}

int	is_set(char c, char const *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

// int	ft_strlen(char *src)
// {
// 	int	i;

// 	i = 0;
// 	while (*src)
// 	{
// 		i++;
// 		src++;
// 	}
// 	return (i);
// }

// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>

// ここに ft_strtrim 関数の定義を挿入

// void test_ft_strtrim(char const *test_str, char const *set,
// char const *expected_result) {
//     char *result = ft_strtrim(test_str, set);
//     if (strcmp(result, expected_result) == 0) {
//         printf("OK: [%s] with set [%s] -> [%s]\n", test_str, set, result);
//     } else {
//         printf("FAIL: [%s] with set [%s]. Expected [%s],
//  but got [%s]\n", test_str, set, expected_result, result);
//     }
//     free(result);
// }

// int main(void) {
//     test_ft_strtrim("+81-80-4092-2371", "+-", "81-80-4092-2371");
//     test_ft_strtrim("   Hello, World!   ", " ", "Hello, World!");
//     test_ft_strtrim("abcXYZabc", "abc", "XYZ");
//     test_ft_strtrim("trimNoSet", "", "trimNoSet");
//     test_ft_strtrim("noMatchingChars", "xyz", "noMatchingChars");
//     test_ft_strtrim("", "+-", ""); // 空文字列のテスト
//     // 任意の追加テストケースをここに挿入
//     return (0);
// }

// #include <stdio.h>

// int main (void)
// {
//     char str[] = "+81-80-4092-2371";
//     char set[] = "+-";

//     // printf("mine: %d", ft_strtrim(str, set));
//     char *result = ft_strtrim(str, set);
//     printf("mine: %s", result);
// }