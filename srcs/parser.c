/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktsukamo <ktsukamo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 08:53:11 by yoshiminaok       #+#    #+#             */
/*   Updated: 2024/07/17 23:21:00 by ktsukamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	parse_token(t_token *ptr, t_fd saved_fd, t_var **varlist);
void	parse_newline(t_token **ptr, t_parser *parser);
void	parse_pipe(t_token **ptr, t_parser *parser);
void	parse_redirect(t_token **ptr, t_parser *parser);
void	parse_command(t_token **ptr, t_parser *parser);
int		get_argsize(t_token *ptr);
void	free_argv(char **argv);

void	parse_token(t_token *ptr, t_fd saved_fd, t_var **varlist)
{
	t_parser	parser;

	if (ptr == NULL)
		return ;
	parser.argv = NULL;
	parser.count = 0;
	parser.redirect_flag = PIPE_AND_EXECVE;
	parser.fd = saved_fd;
	parser.varlist = varlist;
	parse_newline(&ptr, &parser);
	if (ptr == NULL && parser.argv)
	{
		if (parser.redirect_flag != FILE_ERROR)
		{
			interpret(parser.argv);
		}
		free_argv(parser.argv);
	}
}

void	parse_newline(t_token **ptr, t_parser *parser)
{
	parse_pipe(ptr, parser);
	while (*ptr)
	{
		if ((*ptr)->type == NEWLINE)
		{
			if (parser->argv)
			{
				interpret(parser->argv);
				free_argv(parser->argv);
				*ptr = (*ptr)->next;
			}
			parse_pipe(ptr, parser);
		}
		else
		{
			break ;
		}
	}
}

void	parse_pipe(t_token **ptr, t_parser *parser)
{
	parse_command(ptr, parser);
	while (*ptr)
	{
		if ((*ptr)->type == PIPE)
		{
			if (parser->redirect_flag == PIPE_AND_EXECVE)
			{
				pipe_and_execute(parser->argv);
				//  wait関数のためにカウント
				parser->count++;
			}
			else if (parser->redirect_flag == EXECVE_ONLY)
			{
				interpret(parser->argv);
				parser->redirect_flag = PIPE_AND_EXECVE;
				reinit_fd(parser->fd);
			}
			else if (parser->redirect_flag == FILE_ERROR)
				parser->redirect_flag = PIPE_AND_EXECVE;
			free_argv(parser->argv);
			*ptr = (*ptr)->next;
			parse_command(ptr, parser);
		}
		else
		{
			break ;
		}
	}
}

void	parse_command(t_token **ptr, t_parser *parser)
{
	int	size;
	int	i;

	size = get_argsize(*ptr);
	// printf("size:%d\n", size);
	i = 0;
	parser->argv = (char **)malloc(sizeof(char *) * (size + 1));
	if (!parser->argv)
		handle_malloc_error();
	while (i < size)
	{
		if (((*ptr)->type != INPUT_REDIRECTION && (*ptr)->type != HEREDOCUMENT
				&& (*ptr)->type != OUTPUT_REDIRECTION
				&& (*ptr)->type != OUTPUT_APPENDING))
		{
			if ((*ptr)->type == WORD_EXPANDED || (*ptr)->type == QUOTE_EXPANDED)
			{
				parser->argv[i] = get_expanded_argv((*ptr)->token,
						parser->varlist);
			}
			else
			{
				parser->argv[i] = ft_strdup((*ptr)->token);
			}
			if (!parser->argv[i])
				handle_malloc_error();
			i++;
			(*ptr) = (*ptr)->next;
		}
		while (((*ptr) && ((*ptr)->type == INPUT_REDIRECTION
					|| (*ptr)->type == HEREDOCUMENT
					|| (*ptr)->type == OUTPUT_REDIRECTION
					|| (*ptr)->type == OUTPUT_APPENDING)))
		{
			if ((*ptr)->type == HEREDOCUMENT)
				reinit_fd(parser->fd);
			parser->redirect_flag = redirect(ptr);
		}
	}
	parser->argv[i] = NULL;
}

int	get_argsize(t_token *ptr)
{
	t_token	*l;
	int		size;

	l = ptr;
	size = 0;
	while (l->type != PIPE && l->type != NEWLINE)
	{
		if (l->type == INPUT_REDIRECTION || l->type == HEREDOCUMENT
			|| l->type == OUTPUT_REDIRECTION || l->type == OUTPUT_APPENDING)
		{
			// 後でValidateする別関数を作る
			if (l->next == NULL)
				fatal_error("is NULL after Redirect");
			l = l->next;
			if (l->type == INPUT_REDIRECTION || l->type == HEREDOCUMENT
				|| l->type == OUTPUT_REDIRECTION || l->type == OUTPUT_APPENDING)
			{
				printf("minishelsyntax error near unexpected token `%s'\n",
					l->token);
			}
		}
		else
			size++;
		if (l->next == NULL)
			break ;
		l = l->next;
	}
	return (size);
}

void	free_argv(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		free(argv[i]);
		i++;
	}
	free(argv);
}
