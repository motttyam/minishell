/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktsukamo <ktsukamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 14:19:50 by ktsukamo          #+#    #+#             */
/*   Updated: 2024/04/20 16:36:41 by ktsukamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	int		result;

	i = 0;
	if (n == 0)
		return (0);
	result = 0;
	while ((s1[i] || s2[i]) && i < n)
	{
		result = (unsigned char)s1[i] - (unsigned char)s2[i];
		if (s1[i] != s2[i])
			return (result);
		i++;
	}
	return (result);
}
