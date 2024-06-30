/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktsukamo <ktsukamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 19:10:43 by motttyam          #+#    #+#             */
/*   Updated: 2024/04/21 17:38:06 by ktsukamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*dest;
	size_t	dstsize;

	if (!s)
		return (NULL);
	if (start >= (unsigned int)ft_strlen((char *)s))
	{
		dest = (char *)malloc(sizeof(char) * 1);
		if (!dest)
			return (NULL);
		dest[0] = '\0';
		return (dest);
	}
	if (len <= ft_strlen(s) - (size_t)start)
		dstsize = len;
	else
		dstsize = ft_strlen(s) - (size_t)start;
	dest = (char *)malloc(sizeof(char) * (dstsize + 1));
	if (!dest)
		return (0);
	ft_strlcpy(dest, s + start, dstsize + 1);
	return (dest);
}
