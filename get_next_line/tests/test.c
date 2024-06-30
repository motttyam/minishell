// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   test.c                                             :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: ktsukamo <ktsukamo@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2024/04/28 11:34:23 by ktsukamo          #+#    #+#             */
// /*   Updated: 2024/04/29 15:24:54 by ktsukamo         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s);

int	main(int argc, char *argv[])
{
	char *line;
	int fd;

	if (argc == 1)
	{
		line = get_next_line(0);
		while (line)
		{
			write(1, line, ft_strlen(line));
			free(line);
			line = get_next_line(0);
		}
		free(line);
		return (0);
	}
	else if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		if (fd == -1)
			return (0);
		line = get_next_line(fd);
		while (line)
		{
			write(1, line, ft_strlen(line));
			free(line);
			line = get_next_line(fd);
		}
		free(line);
		close(fd);
		return (0);
	}
	else
		write(1, "Too many files\n", 16);
	return (0);
}

size_t	ft_strlen(const char *s)
{
	size_t	length;

	length = 0;
	while (s[length] != '\0')
	{
		length++;
	}
	return (length);
}

// __attribute__((destructor)) static void destructor()
// {
// 	system("leaks -q a.out");
// }