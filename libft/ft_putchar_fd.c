/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   30_ft_putchar_fd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktsukamo <ktsukamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 22:14:06 by ktsukamo          #+#    #+#             */
/*   Updated: 2024/04/15 22:21:56 by ktsukamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

// int main(void)
// {
//     int fd;
//     char c;

//     // 標準出力へ書き込むテスト
//     c = 'A';
//     ft_putchar_fd(c, 1);
//     write(1, "\n", 1);

//     // 標準エラー出力へ書き込むテスト
//     c = 'B';
//     ft_putchar_fd(c, 2);
//     write(2, "\n", 1);

//     // ファイルへ書き込むテスト
//     fd = open("test.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
//     if (fd == -1)
//     {
//         write(STDERR_FILENO, "Error opening file\n", 20);
//         return (1);
//     }
//     c = 'C';
//     ft_putchar_fd(c, fd);
//     close(fd);

//     return (0);
// }