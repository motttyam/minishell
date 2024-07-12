/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshiminaoki <yoshiminaoki@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 08:53:11 by yoshiminaok       #+#    #+#             */
/*   Updated: 2024/07/12 21:42:04 by yoshiminaok      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void parse_token(t_token *lexer);
void parse_newline(t_token **ptr, t_command *cmd);
void parse_pipe(t_token **ptr, t_command *cmd);
void parse_redirect(t_token **ptr, t_command *cmd);
void parse_command(t_token **ptr, t_command *cmd);
int get_argsize(t_token *ptr);
void free_cmd(char **cmd);

void parse_token(t_token *ptr) 
{
    t_command cmd;
    if (ptr == NULL)
        return;
    cmd.argv = NULL;
    cmd.count = 0;
    parse_newline(&ptr, &cmd);
    if (ptr->next == NULL && cmd.argv) 
    {
        interpret(cmd.argv);
        free_cmd(cmd.argv);
    } 
}

void parse_newline(t_token **ptr, t_command *cmd) 
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
            break;
        }
    }
}

void parse_pipe(t_token **ptr, t_command *cmd) 
{
    parse_command(ptr, cmd);
    while (1) 
    {
        if ((*ptr)->type == PIPE) 
        {
            pipe_and_execute(cmd->argv);
            cmd->count++;
            free_cmd(cmd->argv);
            *ptr = (*ptr)->next;
            parse_command(ptr, cmd);
        } 
        else 
        {
            break;
        }
    }
}

// void parse_redirect(t_token **ptr, t_command *cmd) {
//     if ((*ptr)->type == WORD) 
//     {
//         parse_command(ptr, cmd);
//     }
//     while (1) 
//     {
//         if ((*ptr)->type == INPUT_REDIRECTION) 
//         {
//             //redirectの処理を行う関数を作る
//             if (!*cmd) 
//             {
//                 parse_command(ptr, cmd);
//             }
//         } 
//         else 
//         {
//             break;
//         }
//     }
// }

void parse_command(t_token **ptr, t_command *cmd) 
{
    int size = get_argsize(*ptr);
    int i = 0;

    cmd->argv = (char **)malloc(sizeof(char *) * (size + 1));
    if (!cmd->argv)
        handle_malloc_error();
    while (i < size) 
    {
        cmd->argv[i] = ft_strdup((*ptr)->token);
        if (!cmd->argv[i])
            handle_malloc_error();
        i++;
        if ((*ptr)->next)
            (*ptr) = (*ptr)->next;
    }
    cmd->argv[i] = NULL;
}

int get_argsize(t_token *ptr) 
{
    t_token *l = ptr;
    int size = 0;

    while (l->type == WORD) 
    {
        size++;
        if (l->next == NULL)
            break;
        l = l->next;
    }
    return size;
}

void free_cmd(char **cmd) 
{
    int i;

    i = 0;
    while (cmd[i]) 
    {
        free(cmd[i]);
        i++;
    }
    free(cmd);
}
