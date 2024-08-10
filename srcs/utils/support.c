/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   support.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyoshimi <nyoshimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 21:49:17 by nyoshimi          #+#    #+#             */
/*   Updated: 2024/08/10 16:03:21 by nyoshimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_strjoinendl(char *s1, char const *s2)
{
	int		i;
	int		len_s1;
	int		len_s2;
	char	*dest;
	char	*temp;

	len_s1 = ft_strlen_nocrash(s1);
	len_s2 = ft_strlen_nocrash(s2);
	dest = (char *)malloc(sizeof(char) * (len_s1 + len_s2) + 2);
	temp = dest;
	if (!dest)
		fatal_error("malloc");
	i = 0;
	while (s1 && s1[i])
		*dest++ = s1[i++];
	i = 0;
	while (s2[i])
		*dest++ = s2[i++];
	*dest = '\n';
	*(dest + 1) = '\0';
	free(s1);
	return (temp);
}

size_t	ft_strlen_nocrash(const char *s)
{
	size_t	length;

	if (!s)
		return (0);
	length = 0;
	while (s[length] != '\0')
	{
		length++;
	}
	return (length);
}

int	ft_isspace(int c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r')
		return (1);
	else
		return (0);
}

char	*ft_strchr(const char *str, int c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ((unsigned char)str[i] == (unsigned char)c)
			return ((char *)&str[i]);
		i++;
	}
	if ((char)c == '\0')
		return ((char *)&str[i]);
	return (0);
}

void	dup_and_put_error(char **dup, char *src)
{
	*dup = ft_strdup(src);
	if (!(*dup))
		fatal_error("malloc");
}
