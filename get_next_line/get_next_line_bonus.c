/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktsukamo <ktsukamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 16:44:05 by ktsukamo          #+#    #+#             */
/*   Updated: 2024/05/04 16:43:29 by ktsukamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	char	*dest;
	int		c;
	int		dest_size;
	int		new_size;

	dest = NULL;
	dest_size = 0;
	new_size = 0;
	if (fd < 0 || fd > OPEN_MAX || fd > INT_MAX)
		return (NULL);
	c = ft_getchar(fd);
	if (c != -1)
		dest = ft_getstr(fd, c, dest_size, new_size);
	if (!dest)
		return (NULL);
	else
		return (dest);
}

char	*ft_getstr(int fd, int c, int dest_size, int new_size)
{
	char	*temp;
	char	*dest;

	dest = NULL;
	while (c > 0)
	{
		if (c == '\n')
			return (ft_nl_terminate(c, temp, dest, dest_size));
		if (dest_size == new_size)
		{
			temp = ft_realloc(dest, new_size + 1000, 999);
			if (!temp)
				return (free(dest), NULL);
			free(dest);
			dest = temp;
			new_size += 1000;
		}
		dest[dest_size++] = c;
		c = ft_getchar(fd);
	}
	if (c == EOF && dest_size > 0)
		return (ft_terminate(temp, dest, dest_size));
	return (free(dest), NULL);
}

int	ft_getchar(int fd)
{
	static t_gnl_data	gnl[OPEN_MAX];

	if (gnl[fd].n == 0)
	{
		gnl[fd].n = read(fd, gnl[fd].buf, sizeof(gnl[fd].buf));
		gnl[fd].bufp = gnl[fd].buf;
		if (gnl[fd].n == 0)
			return (EOF);
		if (gnl[fd].n == -1)
		{
			gnl[fd].n = 0;
			ft_bzero(gnl[fd].buf, BUFFER_SIZE);
			return (-2);
		}
	}
	if (gnl[fd].n > 0)
	{
		gnl[fd].n--;
		return ((unsigned char)*gnl[fd].bufp++);
	}
	else
		return (EOF);
}

char	*ft_nl_terminate(int c, char *temp, char *dest, int dest_size)
{
	temp = ft_realloc(dest, dest_size + 2, 1);
	if (!temp)
		return (free(dest), NULL);
	free(dest);
	dest = temp;
	dest[dest_size] = c;
	dest[dest_size + 1] = '\0';
	return (dest);
}

char	*ft_terminate(char *temp, char *dest, int dest_size)
{
	temp = ft_realloc(dest, dest_size + 1, 0);
	if (!temp)
		return (free(dest), NULL);
	free(dest);
	dest = temp;
	dest[dest_size] = '\0';
	return (dest);
}
