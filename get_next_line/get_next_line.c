/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktsukamo <ktsukamo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 19:44:59 by nyoshimi          #+#    #+#             */
/*   Updated: 2024/08/11 18:52:05 by ktsukamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// __attribute__((destructor))
// static void destructor() {
//     system("leaks -q a.out");
// }

char	*get_next_line(int fd)
{
	static char	save[BUFFER_SIZE] = {};
	char		*result;
	char		*str;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE >= 2147483647)
		return (NULL);
	str = NULL;
	str = ft_strjoin(str, save);
	if (str == NULL)
		return (NULL);
	str = read_file_gnl(fd, str);
	if (str == NULL)
	{
		ft_memset(save, 0, ft_strlen(save));
		free(str);
		return (NULL);
	}
	result = get_oneline(str);
	ft_save(str, save);
	free(str);
	return (result);
}

char	*read_file_gnl(int fd, char *str)
{
	int		byte;
	char	*buf;
	char	*temp;

	buf = (char *)malloc(BUFFER_SIZE + 1);
	buf[0] = '\0';
	byte = 1;
	while (byte > 0 && check_newline(str))
	{
		byte = read(fd, buf, BUFFER_SIZE);
		if (byte == -1)
			return (free(buf), free(str), NULL);
		if (byte == 0 && buf[0] != '\0')
		{
			byte = 1;
			continue ;
		}
		buf[byte] = '\0';
		temp = str;
		str = ft_strjoin(str, buf);
		free(temp);
		if (!str)
			break ;
	}
	return (free(buf), str);
}

size_t	line_len(char *str)
{
	size_t	count;

	count = 0;
	while (str[count] != '\n' && str[count])
		count++;
	if (str[count] == '\n')
		count++;
	return (count);
}

char	*get_oneline(char *str)
{
	char	*r;
	size_t	i;

	i = 0;
	if (str[0] == '\0')
		return (NULL);
	r = (char *)malloc(line_len(str) + 1);
	if (!r)
		return (NULL);
	i = 0;
	while (str[i] != '\n' && str[i])
	{
		r[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
	{
		r[i] = '\n';
		r[i + 1] = '\0';
	}
	else
		r[i] = '\0';
	return (r);
}

void	ft_save(char *str, char *save)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (str[i] != '\n' && str[i] != '\0')
		i++;
	if (str[i] == '\n')
	{
		i++;
		while (str[i + j] != '\0')
		{
			save[j] = str[i + j];
			j++;
		}
		save[j] = '\0';
	}
	else
		save[0] = '\0';
}

// #include <fcntl.h>
// #include <stdio.h>

// int	main(void)
// {
// 	int fd = open("test.txt", O_RDONLY);
// 	char *line = "";
// 	while (line)
// 	{
// 		line = get_next_line(fd);
// 		printf("fd-line:%s", line);
// 		free(line);
// 	}
// 	return (0);
// }