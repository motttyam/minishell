/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   27_ft_itoa.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktsukamo <ktsukamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 12:34:59 by motttyam          #+#    #+#             */
/*   Updated: 2024/04/15 22:21:41 by ktsukamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

int		count_place(long int n);
void	num_to_digits(long int n, char *digits);

char	*ft_itoa(int n)
{
	char		*digits;
	long int	num;
	int			place;
	int			flag;

	num = n;
	flag = 0;
	if (num < 0)
	{
		flag = 1;
		num = -num;
	}
	place = (count_place(num)) + flag;
	digits = (char *)malloc(sizeof(char) * (place + 1));
	if (!digits)
		return (NULL);
	if (flag)
		*digits = '-';
	num_to_digits(num, digits + place - 1);
	*(digits + place) = '\0';
	return (digits);
}

int	count_place(long int n)
{
	int	place;

	place = 1;
	while (n >= 10)
	{
		place++;
		n /= 10;
	}
	return (place);
}

void	num_to_digits(long int n, char *digits)
{
	if (n >= 10)
		num_to_digits(n / 10, digits - 1);
	*digits = (n % 10) + '0';
	return ;
}

// #include <limits.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>

// // ここに ft_itoa とその他必要な関数の実装を挿入

// void test_itoa(int n) {
//     char *result = ft_itoa(n);
//     printf("ft_itoa(%d) = %s\n", n, result);
//     free(result);
// }

// int main(void) {
//     test_itoa(123);           // 基本的な正の数
//     test_itoa(-123);          // 基本的な負の数
//     test_itoa(0);             // ゼロ
//     test_itoa(INT_MAX);       // 最大整数値
//     test_itoa(INT_MIN);       // 最小整数値 (注意: オーバーフロー問題)
//     test_itoa(9);             // 正の単一桁
//     test_itoa(-9);            // 負の単一桁

//     // 任意の追加テストケースをここに挿入
//     return (0);
// }
