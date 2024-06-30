/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   35_ft_lstadd_front.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktsukamo <ktsukamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 11:39:29 by motttyam          #+#    #+#             */
/*   Updated: 2024/04/15 22:22:34 by ktsukamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (lst == NULL || new == NULL)
		return ;
	new->next = *lst;
	*lst = new;
}

// #include <stdio.h>
// #include <stdlib.h>

// t_list	*ft_lstnew(void *content)
// {
// 	t_list	*new;

// 	new = (t_list *)malloc(sizeof(t_list));
// 	if (new == NULL)
// 		return (NULL);
// 	new->content = content;
// 	new->next = NULL;
// 	return (new);
// }

// // 簡潔なテスト関数
// void test_ft_lstadd_front(void)
// {
//     t_list *list = NULL;
//     t_list *new_element1 = ft_lstnew("First");
//     t_list *new_element2 = ft_lstnew("Second");

//     // テストケース1: リストが空の場合の追加
//     ft_lstadd_front(&list, new_element1);
//     if (list == new_element1)
//         printf("Test1 passed: front of empty list.\n");
//     else
//         printf("Test2 NG:\n");

//     // テストケース2: リストに要素がある場合の追加
//     ft_lstadd_front(&list, new_element2);
//     if (list == new_element2 && list->next == new_element1)
//         printf("Test2 passed:\n");
//     else
//         printf("Test2 failed:\n");

//     // テストで使用したメモリの解放
//     free(new_element1);
//     free(new_element2);
// }

// int main(void)
// {
//     test_ft_lstadd_front(); // テスト関数の実行
//     return (0);
// }
