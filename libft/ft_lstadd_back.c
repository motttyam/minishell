/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   38_ft_lstadd_back.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktsukamo <ktsukamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 12:12:14 by motttyam          #+#    #+#             */
/*   Updated: 2024/04/15 22:22:51 by ktsukamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (!lst || !new)
		return ;
	last = *lst;
	if (!last)
	{
		*lst = new;
		return ;
	}
	while (last->next)
	{
		last = last->next;
	}
	last->next = new;
}

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

// int	ft_lstsize(t_list *lst)
// {
// 	int	length;

// 	length = 0;
// 	while (lst != NULL)
// 	{
// 		lst = lst->next;
// 		length++;
// 	}
// 	return (length);
// }

// int main (void)
// {
//     t_list *list = NULL;

//     t_list *new_element1 = ft_lstnew("1");
//     t_list *new_element2 = ft_lstnew("2");
//     t_list *new_element3 = ft_lstnew("3");
//     t_list *new_element4 = ft_lstnew("4");

//     ft_lstadd_back(&list, new_element1);
//     ft_lstadd_back(&list, new_element2);
//     ft_lstadd_back(&list, new_element3);
//     ft_lstadd_back(&list, new_element4);

//     if (!list)
//     printf("List is empty\n");
//     else
//         while (list)
//         {
//             printf("%s\n", (char *)list->content);
//             list = list->next;
//         }
//     return (0);
// }