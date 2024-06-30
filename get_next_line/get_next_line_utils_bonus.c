/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktsukamo <ktsukamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 16:44:18 by ktsukamo          #+#    #+#             */
/*   Updated: 2024/05/04 16:37:34 by ktsukamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_realloc(void *src, size_t newsize, int flag)
{
	void	*new;

	if (!newsize)
	{
		free(src);
		return (NULL);
	}
	if (!src)
	{
		new = (char *)malloc(sizeof(char) * newsize);
		if (!new)
			return (NULL);
		return (new);
	}
	new = (char *)malloc(sizeof(char) * (newsize));
	if (!new)
		return (NULL);
	ft_memmove((void *)new, (const void *)src, newsize - 1 - flag);
	return (new);
}

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*p_dst;
	unsigned char	*p_src;
	size_t			i;

	p_dst = (unsigned char *)dst;
	p_src = (unsigned char *)src;
	if (dst == src)
		return (dst);
	if (p_dst >= p_src && p_dst < p_src + len)
	{
		i = len;
		while (i > 0)
		{
			i--;
			p_dst[i] = p_src[i];
		}
	}
	else
	{
		i = 0;
		while (i++ < len)
			p_dst[i - 1] = p_src[i - 1];
	}
	return (dst);
}

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*ptr;
	size_t			i;

	ptr = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		ptr[i] = '\0';
		i++;
	}
	return ;
}
