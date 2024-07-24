/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktsukamo <ktsukamo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 19:33:16 by nyoshimi          #+#    #+#             */
/*   Updated: 2024/07/24 22:22:52 by ktsukamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_atol_for_status(char *num);
int	is_long_over_flow(int	synbol,int	result, int	next);
void	put_numeric_error(char *argv);

void	exec_exit(char **argv,int *status)
{
	int	arg_status;

	ft_putendl_fd("exit",1);
	if (ft_argvlen(argv) > 2)
		{
			put_error_message("exit","too many arguments");
			return;
		}
	else if (ft_argvlen(argv) == 1)
		exit(*status);
	else
	{
		arg_status = ft_atol_for_status(argv[1]);
		fprintf(stderr,"stat = %d\n",arg_status);
		if(arg_status == -1)
			put_numeric_error(argv[1]);
		else
			exit (arg_status);
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
	if(num[i] == '+' || num[i] == '-')
	{
		if (num[i] == '-')
			symbol = -1;
		i++;
	}
	if(!ft_isdigit(num[i]))
		return (-1);
	while(num[i])
	{
		if(!ft_isdigit(num[i]) || is_long_over_flow(symbol,result,num[i] - '0'))
			return (-1);
		result = result*10 + (num[i] - '0');
		i++;
	}
	return ((unsigned int)((symbol * result) % 256));	
}

int	is_long_over_flow(int	synbol,int	result, int	next)
{
	if(synbol == 1)
	{
		if(result > (LONG_MAX - next) / 10)
			return (1);
	}
	else
	{
		if((-1) * result < (LONG_MIN + next) / 10)
			return (1);
	}
	return (0);
}

void	put_numeric_error(char *argv)
{
	ft_putstr_fd("minishell: ",2);
	ft_putstr_fd("exit: ",2);
	ft_putstr_fd(argv,2);
	ft_putstr_fd(": ",2);
	ft_putendl_fd("numeric argument required",2);
}	