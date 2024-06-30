/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktsukamo <ktsukamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 18:27:29 by motttyam          #+#    #+#             */
/*   Updated: 2024/04/20 12:30:17 by ktsukamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t	total_size;
	void	*result;

	if (count && size && count > SIZE_MAX / size)
		return (NULL);
	total_size = count * size;
	result = (void *)malloc(total_size);
	if (!result)
	{
		free(result);
		return (NULL);
	}
	ft_bzero(result, total_size);
	return (result);
}

// #include <stdio.h>
// #include <stdlib.h>

// int main() {
//     int i;
//     int numElements = 10;
//     int *arr = (int*)ft_calloc(numElements, sizeof(int));

//     if (arr == NULL) {
//         printf("Memory allocation failed\n");
//         return (1);
//     }

//     // 配列のすべての要素が0で初期化されていることを確認
//     for (i = 0; i < numElements; i++) {
//         if (arr[i] != 0) {
//             printf("Test failed: Element %d is not initialized to 0\n", i);
//             free(arr);
//             return (1);
//         }
//     }

//     printf("Test passed: All elements are initialized to 0\n");

//     free(arr); // 割り当てたメモリを解放
//     return (0);
// }