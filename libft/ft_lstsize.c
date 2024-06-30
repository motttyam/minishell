/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   36_ft_lstsize.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktsukamo <ktsukamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 11:54:48 by motttyam          #+#    #+#             */
/*   Updated: 2024/04/15 22:22:40 by ktsukamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

int	ft_lstsize(t_list *lst)
{
	int	length;

	length = 0;
	while (lst != NULL)
	{
		lst = lst->next;
		length++;
	}
	return (length);
}

// int main (void)
// {
//     t_list *list = NULL;
//     t_list *new_element1 = ft_lstnew("1");
//     t_list *new_element2 = ft_lstnew("2");
//     t_list *new_element3 = ft_lstnew("3");
//     t_list *new_element4 = ft_lstnew("4");
//     ft_lstadd_front(&list, new_element1);
//     ft_lstadd_front(&list, new_element2);
//     ft_lstadd_front(&list, new_element3);
//     ft_lstadd_front(&list, new_element4);

//     printf("length:%d\n", ft_lstsize(list));
//     return (0);
// }