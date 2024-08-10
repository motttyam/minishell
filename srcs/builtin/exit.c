/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktsukamo <ktsukamo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 19:33:16 by nyoshimi          #+#    #+#             */
/*   Updated: 2024/08/10 16:44:31 by ktsukamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	exec_exit(char **argv, int *status, t_tool *tool)
{
	int	arg_status;

	ft_putendl_fd("exit", 1);
	if (ft_argvlen(argv) == 1)
	{
		// if (g_signal.sigint == 1)
		// 	*status = 130;
		exit(*status);
	}
	else
	{
		arg_status = ft_atol_for_status(argv[1]);
		if (arg_status == -1)
			put_numeric_error(argv[1]);
		else if (ft_argvlen(argv) > 2)
		{
			put_error_message("exit", "too many arguments", tool);
			return ;
		}
		else
			exit(arg_status);
	}
}

int	ft_atol_for_status(char *num)
{
	long	result;
	int		i;
	int		symbol;

	result = 0;
	i = 0;
	symbol = 1;
	while (ft_isspace(num[i]))
		i++;
	get_symbol(num[i], &symbol, &i);
	if (!ft_isdigit(num[i]))
		return (-1);
	while (ft_isdigit(num[i]))
	{
		if (is_long_over_flow(symbol, result, num[i] - '0'))
			return (-1);
		result = result * 10 + (num[i] - '0');
		i++;
	}
	while (ft_isspace(num[i]))
		i++;
	if (num[i] != '\0')
		return (-1);
	return ((unsigned int)((symbol * result) % 256));
}

void	get_symbol(char c, int *symbol, int *i)
{
	if (c == '+' || c == '-')
	{
		if (c == '-')
			*symbol = -1;
		(*i)++;
	}
}

int	is_long_over_flow(int synbol, long result, int next)
{
	if (synbol == 1)
	{
		if (result > (LONG_MAX - next) / 10)
			return (1);
	}
	else
	{
		if ((-1) * result < (LONG_MIN + next) / 10)
			return (1);
	}
	return (0);
}

void	put_numeric_error(char *argv)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd("exit: ", 2);
	ft_putstr_fd(argv, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd("numeric argument required", 2);
	exit(2);
}
