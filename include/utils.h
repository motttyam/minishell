/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyoshimi <nyoshimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 14:05:16 by ktsukamo          #+#    #+#             */
/*   Updated: 2024/08/04 15:04:28 by nyoshimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

void	save_fd(t_fd *saved_fd);
void	reinit_fd(t_fd saved_fd);
void	close_fd(t_fd saved_fd);

typedef enum s_var_state
{
	SHELL,
	ENV,
}		t_var_state;

void	get_envlist(t_var **list);
t_var	*get_new_var(int i, char **environ);
void	add_last_newvar(t_var *first, t_var *new);

// error.c
void	fatal_error(const char *msg) __attribute__((noreturn));
void	handle_malloc_error(void);
void	quote_error(void);
void	put_error_message(char *argv, char *message, t_tool *tool);

// support.c
char	*ft_strjoinendl(char *s1, char const *s2);
size_t	ft_strlen_nocrash(const char *s);
int		ft_isspace(int c);
char	*ft_strchr(const char *str, int c);
void	dup_and_put_error(char **dup,char *src);

// free.c
void	free_token_lexer(t_token *head);
void	free_argv(char **argv);
void	free_envlist(t_var *head);

#endif