/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyoshimi <nyoshimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 00:15:41 by nyoshimi          #+#    #+#             */
/*   Updated: 2024/08/11 15:36:52 by nyoshimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int		check_option(char *argv);

void	exec_echo(char **argv, t_tool *tool)
{
	int	i;
	int	option_flg;

	i = 1;
	option_flg = 0;
	while (argv[i])
	{
		if (check_option(argv[i]))
			option_flg = 1;
		else
			break ;
		i++;
	}
	while (argv[i])
	{
		ft_putstr_fd(argv[i], 1);
		i++;
		if (argv[i])
			ft_putchar_fd(' ', 1);
	}
	if (!option_flg)
		ft_putchar_fd('\n', 1);
	tool->status = 0;
}

int	check_option(char *argv)
{
	int	i;

	i = 1;
	if (argv[0] != '-')
		return (0);
	while (argv[i])
	{
		if (argv[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}
