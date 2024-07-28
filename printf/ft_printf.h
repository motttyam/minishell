#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <limits.h>
# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

// ft_putchar_fd.c
int		printf_putchar_fd(char c, int fd);

// ft_putstr_fd.c
int		printf_putstr_fd(char *s, int fd);

// ft_puthex.c
int		ft_puthex(long int num, int flag, int fd);
void	ft_puthex_recursive(long int num, int *count, int flag, int fd);

// ft_puthex_uns.c
int		ft_puthex_uns(unsigned long int num, int fd);
void	ft_puthex_uns_recursive(unsigned long int num, int *count, int fd);

// ft_strlen.c
size_t	printf_strlen(const char *s);

// ft_putnbr.c
int		printf_putnbr_fd(int n, int fd);
void	printf_put_recursive(int n, int fd, int *count);

// ft_putnbr_uns.c
void	putnbr_uns_recursive(unsigned int n, int fd, int *count);
int		ft_putnbr_uns_fd(unsigned int n, int fd);

// ft_printf.c
int		ft_printf_fd(int fd, const char *format, ...);
int		ft_count_format(int fd, va_list *args, const char *format);
int		ft_handle_format(int fd, va_list *args, char c);

#endif