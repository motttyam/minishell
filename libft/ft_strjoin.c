/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   24_ft_strjoin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktsukamo <ktsukamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 21:42:50 by ktsukamo          #+#    #+#             */
/*   Updated: 2024/04/19 23:15:09 by ktsukamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		len_s1;
	int		len_s2;
	char	*dest;
	char	*temp;

	if (!s1)
		return (NULL);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	dest = (char *)malloc(sizeof(char) * (len_s1 + len_s2) + 1);
	temp = dest;
	if (!dest)
		return (NULL);
	i = 0;
	while (s1[i])
		*dest++ = s1[i++];
	i = 0;
	while (s2[i])
		*dest++ = s2[i++];
	*dest = '\0';
	return (temp);
}

// int main (void)
// {
// 	char s1[] = "Kazuki";
// 	char s2[] = "Tsukamoto";
// 	char *dest;

// 	dest = ft_strjoin(s1, s2);
// 	printf("%s", dest);
// 	return (0);
// }