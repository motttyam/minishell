/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   41_ft_lstiter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktsukamo <ktsukamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 14:29:42 by motttyam          #+#    #+#             */
/*   Updated: 2024/04/15 22:23:19 by ktsukamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (!lst)
		return ;
	while (lst)
	{
		f(lst->content);
		lst = lst->next;
	}
}

// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>

// void print_element(void *content)
// {
//     char *prefix = "Element: ";
//     char *str = (char *)content;
//     char output[100]; // 必要に応じて適切なサイズに調整してください
//     strcpy(output, prefix);
//     strcat(output, str);
//     printf("%s\n", output);
// }
// // テスト関数
// void test_ft_lstiter()
// {
//     t_list *lst = NULL;

//     // テスト用の要素をリストに追加
//     ft_lstadd_back(&lst, ft_lstnew("1"));
//     ft_lstadd_back(&lst, ft_lstnew("2"));
//     ft_lstadd_back(&lst, ft_lstnew("3"));

//     // リストを表示してテスト用の要素が含まれていることを確認
//     printf("List before iterating:\n");
//     print_list(lst);

//     // ft_lstiterを呼び出してリストの各要素に関数を適用
//     printf("\nList after iterating:\n");
//     ft_lstiter(lst, &print_element);
// }

// int main(void)
// {
//     printf("=== Testing ft_lstiter ===\n");
//     test_ft_lstiter();
//     return (0);
// }
