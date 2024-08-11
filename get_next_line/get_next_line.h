/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyoshimi <nyoshimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 12:35:48 by nyoshimi          #+#    #+#             */
/*   Updated: 2024/08/11 12:10:34 by nyoshimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <limits.h>
# include <stdlib.h>
# include <unistd.h>

size_t	ft_strlen(const char *str);
char	*ft_strjoin(char const *s1, char const *s2);
void	*ft_memset(void *buf, int c, size_t n);
int		check_newline(char *s);
char	*get_next_line(int fd);
char	*read_file_gnl(int fd, char *str);
size_t	line_len(char *str);
char	*get_oneline(char *str);
void	ft_save(char *str, char *save);

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif
#endif