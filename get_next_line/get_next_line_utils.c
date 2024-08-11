/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyoshimi <nyoshimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 20:46:36 by nyoshimi          #+#    #+#             */
/*   Updated: 2024/04/29 18:53:35 by nyoshimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t	count;

	count = 0;
	if (str == NULL)
		return (0);
	while (str[count])
		count++;
	return (count);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*r;
	int		i;
	int		j;

	i = 0;
	j = 0;
	r = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (r == NULL)
		return (NULL);
	while (s1 && s1[i])
	{
		r[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		r[i + j] = s2[j];
		j++;
	}
	r[i + j] = '\0';
	return (r);
}

void	*ft_memset(void *buf, int c, size_t n)
{
	unsigned char	*ptr;

	ptr = (unsigned char *)buf;
	while (n > 0)
	{
		*ptr = c;
		++ptr;
		n--;
	}
	return (buf);
}

int	check_newline(char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (1);
	while (s[i])
	{
		if (s[i] == '\n')
			return (0);
		i++;
	}
	return (1);
}
