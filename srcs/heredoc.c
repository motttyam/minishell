/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyoshimi <nyoshimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 21:25:10 by nyoshimi          #+#    #+#             */
/*   Updated: 2024/07/24 18:26:14 by nyoshimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	get_heredoc_input(t_token *delimiter, t_var **list);
char	*get_input_noexpand(t_token *delimiter);
char	*get_input_expand(t_token *delimiter, t_var **list);
char	*ft_strjoinendl(char const *s1, char const *s2);

void    check_heredoc_token(t_token *token, t_var **list)
{
    while(token)
    {
        if(token->type == HEREDOCUMENT)
        {
            token = token->next;
            get_heredoc_input(token,list);
        }
        token = token->next;
    }
}
void get_heredoc_input(t_token *delimiter, t_var **list)
{
	char	*buf;

	
    if(delimiter->type == SINGLE_QUOTE || delimiter->type == DOUBLE_QUOTE || delimiter->type == QUOTE_EXPANDED)
        buf = get_input_noexpand(delimiter);
	else
		buf = get_input_expand(delimiter,list);
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

char	*get_input_expand(t_token *delimiter, t_var **list)
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
			line = get_expanded_argv(line,list,0);
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
