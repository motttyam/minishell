/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktsukamo <ktsukamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 23:56:17 by motttyam          #+#    #+#             */
/*   Updated: 2024/04/20 18:49:11 by ktsukamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!*needle)
		return ((char *)haystack);
	while (i < len && haystack[i])
	{
		while (haystack[i + j] == needle[j] && i + j < len)
		{
			if (!needle[j + 1])
				return ((char *)&haystack[i]);
			j++;
		}
		j = 0;
		i++;
	}
	return (NULL);
}

// #include <stdio.h>
// #include <string.h>

// void test_strnstr(const char *haystack, const char *needle, size_t len,
// const char *expected) {
//     char *result = strnstr(haystack, needle, len);
//     if ((result == expected) || (result && expected && !strcmp(result,
// expected))) {
//         printf("PASS: haystack=\"%s\", needle=\"%s\", len=%zu\n", haystack,
// needle, len);
//     } else {
//         printf("FAIL: haystack=\"%s\", needle=\"%s\",
// len=%zu (expected \"%s\", got \"%s\")\n",
//                haystack, needle, len, expected ? expected : "NULL",
// result ? result : "NULL");
//     }
// }

// int main() {
//     // テストケース1: needleがhaystackの先頭にある場合
//     test_strnstr("helld world!", "ld!", 12, "ld!");

//     // テストケース2: needleがhaystackの途中にある場合
//     test_strnstr("hello world", "world", 11, "world");

//     // テストケース3: lenがneedleを完全に含まない場合
//     test_strnstr("hello world", "world", 5, NULL);

//     // テストケース4: needleが空の文字列の場合
//     test_strnstr("hello world", "", 11, "hello world");

//     // テストケース5: haystackが空の文字列の場合
//     test_strnstr("", "hello", 0, NULL);

//     // テストケース6: needleがhaystackに存在しない場合
//     test_strnstr("hello world", "test", 11, NULL);

//     // テストケース7: lenが0の場合
//     test_strnstr("hello world", "hello", 0, NULL);

//     // 他のコーナーケースについても同様にテストを追加できます。

//     return (0);
// }