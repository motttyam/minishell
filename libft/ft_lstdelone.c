/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   39*_ft_lstdelone.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktsukamo <ktsukamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 12:52:39 by motttyam          #+#    #+#             */
/*   Updated: 2024/04/15 22:23:02 by ktsukamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (!lst || !del)
		return ;
	del(lst->content);
	free(lst);
}

// void delete_list(void *content)
// {
//    content = (char *)content;
//    return ;
// }

// #include <stdio.h>

// int main (void)
// {
//     t_list *lst = NULL;

//     t_list *new = ft_lstnew("1");
//     ft_lstadd_front(&lst, new);

//     printf("%s\n", (char *)lst->content);
//     ft_lstdelone(lst, delete_list);
//     // printf("%s\n", (char *)lst->content);
//     return (0);
// }