/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   support2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktsukamo <ktsukamo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 11:47:25 by nyoshimi          #+#    #+#             */
/*   Updated: 2024/08/11 18:51:46 by ktsukamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_strncmp_newline(const char *s1, const char *s2, size_t n)
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
		if (s1[i] == '\n' && s2[i] == '\0')
			return (0);
		if (s1[i] != s2[i])
			return (result);
		i++;
	}
	return (result);
}
