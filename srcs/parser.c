/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktsukamo <ktsukamo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 08:53:11 by yoshiminaok       #+#    #+#             */
/*   Updated: 2024/07/14 22:19:13 by ktsukamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	parse_token(t_token *ptr, t_fd saved_fd);
void	parse_newline(t_token **ptr, t_command *cmd);
void	parse_pipe(t_token **ptr, t_command *cmd);
void	parse_redirect(t_token **ptr, t_command *cmd);
void	parse_command(t_token **ptr, t_command *cmd);
int		get_argsize(t_token *ptr);
void	free_cmd(char **cmd);

void	parse_token(t_token *ptr, t_fd saved_fd)
{
	t_command	cmd;

	if (ptr == NULL)
		return ;
	cmd.argv = NULL;
	cmd.count = 0;
	cmd.redirect_flag = 0;
	cmd.fd = saved_fd;
	parse_newline(&ptr, &cmd);
	if (ptr->next == NULL && cmd.argv)
	{
		if (cmd.redirect_flag == 0)
		{
			fprintf(stderr, "command:%s\n", cmd.argv[0]);
			interpret(cmd.argv);
			free_cmd(cmd.argv);
		}
	}
}

void	parse_newline(t_token **ptr, t_command *cmd)
{
	parse_pipe(ptr, cmd);
	while (1)
	{
		if ((*ptr)->type == NEWLINE)
		{
			if (cmd->argv)
			{
				interpret(cmd->argv);
				free_cmd(cmd->argv);
				*ptr = (*ptr)->next;
			}
			parse_pipe(ptr, cmd);
		}
		else
		{
			break ;
		}
	}
}

void	parse_pipe(t_token **ptr, t_command *cmd)
{
	parse_command(ptr, cmd);
	while (1)
	{
		if ((*ptr)->type == PIPE)
		{
			if (cmd->redirect_flag == 0)
			{
				pipe_and_execute(cmd->argv);
				//  wait関数のためにカウント
				// reinit_fd(cmd->fd);
				cmd->count++;
			}
			else
				cmd->redirect_flag = 0;
			free_cmd(cmd->argv);
			*ptr = (*ptr)->next;
			parse_command(ptr, cmd);
		}
		else
		{
			break ;
		}
	}
}

void	parse_command(t_token **ptr, t_command *cmd)
{
	int	size;
	int	i;

	size = get_argsize(*ptr);
	// printf("size:%d\n", size);
	i = 0;
	cmd->argv = (char **)malloc(sizeof(char *) * (size + 1));
	if (!cmd->argv)
		handle_malloc_error();
	while (i < size)
	{
		if (((*ptr)->type == INPUT_REDIRECTION || (*ptr)->type == HEREDOCUMENT
				|| (*ptr)->type == OUTPUT_REDIRECTION
				|| (*ptr)->type == OUTPUT_APPENDING))
		{
			cmd->redirect_flag = redirect(ptr);
		}
		cmd->argv[i] = ft_strdup((*ptr)->token);
		if (!cmd->argv[i])
			handle_malloc_error();
		i++;
		if ((*ptr)->next)
			(*ptr) = (*ptr)->next;
	}
	// printf("token:%s\ntype:%d\n", (*ptr)->token, (*ptr)->type);
	if (((*ptr)->type == INPUT_REDIRECTION || (*ptr)->type == HEREDOCUMENT
			|| (*ptr)->type == OUTPUT_REDIRECTION
			|| (*ptr)->type == OUTPUT_APPENDING))
	{
		cmd->redirect_flag = redirect(ptr);
		fprintf(stderr, "flag3: %d", cmd->redirect_flag);
	}
	cmd->argv[i] = NULL;
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
		// printf("hello\n");
		l = l->next;
	}
	return (size);
}

void	free_cmd(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		free(cmd[i]);
		i++;
	}
	free(cmd);
}
