/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   34_ft_lstnew.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktsukamo <ktsukamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 20:24:55 by motttyam          #+#    #+#             */
/*   Updated: 2024/04/15 22:22:27 by ktsukamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new;

	new = (t_list *)malloc(sizeof(t_list));
	if (new == NULL)
		return (NULL);
	new->content = content;
	new->next = NULL;
	return (new);
}

// #include <stdio.h>

// void test_ft_lstnew(void)
// {
//     int content = 42;
//     t_list *new_element = ft_lstnew(&content);

//     // テストケース1: 新しい要素がNULLでないことを確認
//     if (new_element == NULL)
//     {
//         printf("ft_lstnew failed to allocate memory for new element.\n");
//     }
//     else
//     {
//         // テストケース2: contentの確認
//         if (*((int*)new_element->content) == content)
//         {
//             printf("Test passed:content successfully added\n");
//         }
//         else
//         {
//             printf("Test failed: content is wrong\n");
//         }

//         // テストケース3: nextがNULLかの確認
//         if (new_element->next == NULL)
//         {
//             printf("Test passed:NULL terminated\n");
//         }
//         else
//         {
//             printf("Test failed: NO NULL\n");
//         }
//     }

//     // テストで使用したメモリの解放
//     free(new_element);
// }

// int main(void)
// {
//     test_ft_lstnew(); // テスト関数の実行
//     return (0);
// }