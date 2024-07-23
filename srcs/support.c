/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   support.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyoshimi <nyoshimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 21:49:17 by nyoshimi          #+#    #+#             */
/*   Updated: 2024/07/23 22:14:45 by nyoshimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_strjoinendl(char const *s1, char const *s2)
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
		return (NULL);
	i = 0;
	while (s1 && s1[i])
		*dest++ = s1[i++];
	i = 0;
	while (s2[i])
		*dest++ = s2[i++];
	*dest = '\n';
	*(dest + 1)= '\0';
	return (temp);
}
size_t	ft_strlen_nocrash(const char *s)
{
	size_t	length;

	if(!s)
		return (0);
	length = 0;
	while (s[length] != '\0')
	{
		length++;
	}
	return (length);
}