/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   37_ft_lstlast.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktsukamo <ktsukamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 12:05:01 by motttyam          #+#    #+#             */
/*   Updated: 2024/04/15 22:22:46 by ktsukamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

// #include <stdlib.h>

// // テスト関数
// void test_ft_lstlast(void)
// {
//     t_list *list = NULL;
//     t_list *last_element;

//     // テストケース1: 空のリストの場合
//     last_element = ft_lstlast(list);
//     if (last_element == NULL)
//         printf("Test1 passed\n");
//     else
//         printf("Test1 failed\n");

//     // テストケース2: 要素が1つのリストの場合
//     list = ft_lstnew("First");
//     last_element = ft_lstlast(list);
//     if (last_element == list)
//         printf("Test2 passed\n");
//     else
//         printf("Test2 failed\n");

//     // テストケース3: 複数の要素があるリストの場合
//     t_list *second_element = ft_lstnew("Second");
//     t_list *third_element = ft_lstnew("Third");
//     list->next = second_element;
//     second_element->next = third_element;
//     last_element = ft_lstlast(list);
//     if (last_element == third_element)
//         printf("Test3 passed\n");
//     else
//         printf("Test3 failed\n");

//     // テストで使用したメモリの解放
//     free(list);
//     free(second_element);
//     free(third_element);
// }

// int main(void)
// {
//     test_ft_lstlast(); // テスト関数の実行
//     return (0);
// }
