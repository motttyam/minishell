/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktsukamo <ktsukamo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 21:25:10 by nyoshimi          #+#    #+#             */
/*   Updated: 2024/07/28 17:21:41 by ktsukamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	get_heredoc_input(t_token *delimiter, t_var **list, int *status);
char	*get_input_noexpand(t_token *delimiter);
char	*get_input_expand(t_token *delimiter, t_var **list, int *status);
char	*ft_strjoinendl(char const *s1, char const *s2);

void    check_heredoc_token(t_token *token, t_var **list, int *status)
{
    // g_signal.heredoc_interruption = 1;
	while(token)
    {
        if(token->type == HEREDOCUMENT)
        {
            token = token->next;
            get_heredoc_input(token, list, status);
        }
        token = token->next;
    }
    // g_signal.heredoc_interruption = 0;
}

void get_heredoc_input(t_token *delimiter, t_var **list, int *status)
{
	char	*buf;

    if(delimiter->type == SINGLE_QUOTE || delimiter->type == DOUBLE_QUOTE || delimiter->type == QUOTE_EXPANDED)
        buf = get_input_noexpand(delimiter);
	else
		buf = get_input_expand(delimiter,list, status);
	if(!buf)
		fatal_error("");
	ft_bzero(delimiter->token,ft_strlen(delimiter->token));
	ft_strlcpy(delimiter->token,buf,PATH_MAX);
	free(buf);
	delimiter->type = WORD;
}
char	*get_input_noexpand(t_token *delimiter)
{
    char    *line;
    char	*buf;
	char	*tmp;
	
	buf = NULL;
    while (1)
	{
		line = readline("> ");
		if (!line || !ft_strncmp(line, delimiter->token, ft_strlen(delimiter->token)
				+ 1))
			break ;
		tmp = buf;
		buf = ft_strjoinendl(buf,line);
		if (!buf)
			fatal_error("malloc");
		if (tmp)
			free(tmp);
		free(line);
	}
	return (buf);
}

char	*get_input_expand(t_token *delimiter, t_var **list, int *status)
{
    char    *line;
    char	*buf;
	char	*tmp;
	
	buf = NULL;
    while (1)
	{
		line = readline("> ");
		if (!line || !ft_strncmp(line, delimiter->token, ft_strlen(delimiter->token)
				+ 1))
			break ;
		if (ft_strchr(line,'$'))
		{
			tmp = line;
			line = get_expanded_argv(line,list, status);
			free(tmp);
		}
		tmp = buf;
		buf = ft_strjoinendl(buf,line);
		if (!buf)
			fatal_error("malloc");
		if (tmp)
			free(tmp);
		free(line);
	}
	return (buf);
}
