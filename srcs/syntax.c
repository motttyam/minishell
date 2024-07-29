/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktsukamo <ktsukamo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 22:06:23 by ktsukamo          #+#    #+#             */
/*   Updated: 2024/07/28 22:39:57 by ktsukamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_valid_after_redirect(int type)
{
	char	*type_name;

	type_name = NULL;
	if ((type == INPUT_REDIRECTION || type == HEREDOCUMENT
			|| type == OUTPUT_REDIRECTION || type == OUTPUT_APPENDING))
	{
		if (type == INPUT_REDIRECTION)
			type_name = ft_strdup(">");
		else if (type == HEREDOCUMENT)
			type_name = ft_strdup("<<");
		else if (type == OUTPUT_REDIRECTION)
			type_name = ft_strdup(">");
		else if (type == OUTPUT_APPENDING)
			type_name = ft_strdup(">>");
		ft_printf_fd(2, "minishell: syntax error near unexpected token `%s'\n",
			type_name);
		free(type_name);
		return (-1);
	}
	return (0);
}

int	check_syntaxerror(t_token *token, int *status)
{
	while (token)
	{
		if (token->type == PIPE)
		{
			if (token->next->type == PIPE)
			{
				ft_printf_fd(2,
					"minishell: syntax error near unexpected token `|'\n");
				*status = 2;
				return (-1);
			}
		}
		if ((token->type == INPUT_REDIRECTION
				|| token->type == OUTPUT_REDIRECTION
				|| token->type == OUTPUT_APPENDING))
		{
			if (token->next && is_valid_after_redirect(token->next->type) == -1)
			{
				*status = 2;
				return (-1);
			}
		}
		token = token->next;
	}
	return (0);
}

int	check_last_type(t_token *token, int *status)
{
	while (token)
	{
		while (token->next && token->next->type != TK_NEWLINE)
		{
			token = token->next;
		}
		if (token->next->type == TK_NEWLINE && (token->type == INPUT_REDIRECTION
			|| token->type == OUTPUT_REDIRECTION
			|| token->type == OUTPUT_APPENDING))
		{
			ft_printf_fd(2,
				"minishell: syntax error near unexpected token `newline'\n");
			*status = 2;
			return (-1);
		}
        token = token->next;
	}
    return (0);
}