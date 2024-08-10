/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktsukamo <ktsukamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 14:11:50 by ktsukamo          #+#    #+#             */
/*   Updated: 2024/05/04 16:30:25 by ktsukamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <fcntl.h>
# include <limits.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

// get_next_line.c
char	*get_next_line(int fd);
int		ft_getchar(int fd);
char	*ft_getstr(int fd, int c, int dest_size, int new_size);
char	*ft_terminate(char *temp, char *dest, int dest_size);
char	*ft_nl_terminate(int c, char *temp, char *dest, int dest_size);

// get_next_line_utils.c
char	*ft_realloc(void *str, size_t newsize, int flag);
void	*ft_memmove(void *dst, const void *src, size_t len);
void	ft_bzero(void *s, size_t n);

#endif