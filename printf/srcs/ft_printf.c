/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktsukamo <ktsukamo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 23:44:58 by motttyam          #+#    #+#             */
/*   Updated: 2024/07/28 18:03:08 by ktsukamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int	ft_printf_fd(int fd, const char *format, ...)
{
	va_list		args;
	int			count_format;
	
	va_start(args, format);
	count_format = ft_count_format(fd, &args, format);
	va_end(args);
	return (count_format);
}

int	ft_count_format(int fd, va_list *args, const char *format)
{
	int	count;

	count = 0;
	while (*format)
	{
		if (*format != '%')
		{
			printf_putchar_fd(*format, fd);
			format++;
			count++;
		}
		else
		{
			count += ft_handle_format(fd, args, *(format + 1));
			format += 2;
		}
	}
	return (count);
}

int	ft_handle_format(int fd, va_list *args, char c)
{
	if (c == 'c')
		return (printf_putchar_fd(va_arg(*args, int), fd));
	else if (c == 's')
		return (printf_putstr_fd(va_arg(*args, char *), fd));
	else if (c == 'p')
		return (ft_puthex_uns((unsigned long int)va_arg(*args, void *), fd));
	else if (c == 'd' || c == 'i')
		return (printf_putnbr_fd(va_arg(*args, int), fd));
	else if (c == 'u')
		return (ft_putnbr_uns_fd(va_arg(*args, unsigned int), fd));
	else if (c == 'x')
		return (ft_puthex(va_arg(*args, int), 2, fd));
	else if (c == 'X')
		return (ft_puthex(va_arg(*args, int), 0, fd));
	else if (c == '%')
		return (printf_putchar_fd(c, fd));
	else
		return (0);
}

// %c: 1文字。
// %s: 文字列。
// %p: ポインタのアドレス、16進数。
// %d: 符号付き整数。
// %i: %dと同じ、符号付き整数。
// %u: 符号なし整数。
// %x: 16進数、小文字。
// %X: 16進数、大文字。
// %%: %記号。