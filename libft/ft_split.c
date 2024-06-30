/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktsukamo <ktsukamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 23:17:05 by ktsukamo          #+#    #+#             */
/*   Updated: 2024/04/21 17:47:00 by ktsukamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

static int	word_count(const char *s, char c)
{
	int	count;

	count = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s && *s != c)
		{
			count++;
			while (*s && *s != c)
				s++;
		}
	}
	return (count);
}

int	ft_split2(char **dest, int j, const char *s, int len)
{
	int	k;

	dest[j] = (char *)malloc(sizeof(char) * (len + 1));
	if (!dest[j])
	{
		while (j > 0)
		{
			free(dest[--j]);
		}
		free(dest);
		dest = NULL;
		return (1);
	}
	k = 0;
	while (k < len)
	{
		dest[j][k] = s[k];
		k++;
	}
	dest[j][k] = '\0';
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**dest;
	int		i;
	int		old_i;
	int		j;

	if (!s)
		return (NULL);
	dest = (char **)malloc(sizeof(char *) * (word_count(s, c) + 1));
	if (!dest)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		old_i = i;
		while (s[i] && s[i] != c)
			i++;
		if (old_i < i)
			if (ft_split2(dest, j++, s + old_i, i - old_i) == 1 && !dest)
				return (NULL);
	}
	dest[j] = NULL;
	return (dest);
}

// #include "libft.h"
// #include <stdio.h>
// #include <string.h>

// // Helper function to compare the result of ft_split with expected result
// int	compare_results(char **result, char **expected)
// {
// 	int	i;

// 	i = 0;
// 	while (expected[i] != NULL && result[i] != NULL)
// 	{
// 		if (strcmp(result[i], expected[i]) != 0)
// 			return (0); // Not matching
// 		i++;
// 	}
// 	return ((expected[i] == NULL && result[i] == NULL) ? 1 : 0);
// }

// // Function to free the result of ft_split
// void	free_result(char **result)
// {
// 	if (result != NULL)
// 	{
// 		for (int i = 0; result[i] != NULL; i++)
// 		{
// 			free(result[i]);
// 		}
// 		free(result);
// 	}
// }

// // Test case function for ft_split
// void	test_ft_split(char const *s, char c, char **expected)
// {
// 	char	**result;

// 	result = ft_split(s, c);
// 	printf("Test with input: \"%s\" and delimiter '%c'\n", s, c);
// 	if (compare_results(result, expected))
// 	{
// 		printf("OK\n");
// 	}
// 	else
// 	{
// 		printf("FAIL\n");
// 	}
// 	free_result(result);
// }

// int	main(void)
// {
// 	char	*test1_expected[] = {"hello", "world", "this", "is", "a", "test",
// 			NULL};
// 	char	*test2_expected[] = {"leading", "and", "trailing", "spaces", NULL};
// 	char	*test3_expected[] = {"no_delimiters_here", NULL};
// 	char	*test6_expected[] = {"a", "b", "c", "d", NULL};
// 	char	*test7_expected[] = {"end", "with", "delimiter", NULL};

// 	char *test4_expected[] = {NULL}; // Empty string, no elements
// 	char *test5_expected[] = {NULL}; // Only delimiters
// 	test_ft_split("hello world this is a test", ' ', test1_expected);
// 	test_ft_split("   leading and trailing spaces   ", ' ', test2_expected);
// 	test_ft_split("no_delimiters_here", '-', test3_expected);
// 	test_ft_split("", ' ', test4_expected);
// 	test_ft_split("----", '-', test5_expected);
// 	test_ft_split("a-b-c-d", '-', test6_expected);
// 	test_ft_split("end with delimiter-", '-', test7_expected);
// 	return (0);
// }
