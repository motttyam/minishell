/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   22_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktsukamo <ktsukamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 18:43:05 by ktsukamo          #+#    #+#             */
/*   Updated: 2024/04/18 00:58:00 by ktsukamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

char	*ft_strdup(const char *src)
{
	char	*dest;

	dest = (char *)malloc(sizeof(char) * ft_strlen(src) + 1);
	if (dest == NULL)
		return (NULL);
	ft_strcpy(dest, src);
	return (dest);
}

// int	ft_strlen(const char *src)
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

char	*ft_strcpy(char *dest, const char *src)
{
	int	i;

	i = 0;
	while (*src)
	{
		dest[i] = *src;
		i++;
		src++;
	}
	dest[i] = '\0';
	return (dest);
}

// strdup
// 1. allocate memory for a copy of the string s1
// 1.1.  before finishing function, free the moery I ensured
// 2. does the copy
// 2.1. when using *strcpy, *strcpy returns the pointer of dest
// 3. returns a pointer be used as an argument

// #include <stdio.h>

// int	main(void)
// {
// 	char *original = "Hello, World!";
// 	char *copy = ft_strdup(original);

// 	if (copy)
// 	{
// 		printf("Original: %s\n", original);
// 		printf("Copy: %s\n", copy);
// 		free(copy); // メモリリークを避けるために確保したメモリを解放
// 	}
// 	return (0);
// }
