/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktsukamo <ktsukamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 16:45:27 by motttyam          #+#    #+#             */
/*   Updated: 2024/04/20 19:30:58 by ktsukamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	int	i;

	if (!s || !f)
		return ;
	i = 0;
	while (s[i])
	{
		f(i, &s[i]);
		i++;
	}
	return ;
}

// #include <stdio.h>
// #include <ctype.h>

// void replace_a_with_star(unsigned int i, char *c)
// {
//     (void) i;
//     if (*c == 'a')
//         *c = '*';
// }

// void case_alternator(unsigned int i, char *c) {
//     if (i % 2 == 0)
//         *c = toupper(*c);
//     else
//         *c = tolower(*c);
// }

// void test_empty_string() {
//     char s[] = "";
//     ft_striteri(s, replace_a_with_star);
//     printf("Empty string: \"%s\"\n", s);
// }

// void test_replace_a_with_star()
// {
//     char s[] = "banana";
//     ft_striteri(s, replace_a_with_star);
//     printf("Replace 'a' with '*': %s\n", s);
// }

// void test_case_alternator() {
//     char s[] = "HeLLo, WoRLd!";
//     ft_striteri(s, case_alternator);
//     printf("Case alternator: %s\n", s);
// }

// int main() {
//     test_empty_string();
//     test_replace_a_with_star();
//     test_case_alternator();
//     return (0);
// }
