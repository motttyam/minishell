/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktsukamo <ktsukamo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 14:05:16 by ktsukamo          #+#    #+#             */
/*   Updated: 2024/07/28 14:05:18 by ktsukamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

// var.h
typedef struct s_var
{
	char			*key;
	char			*value;
	int				type;
	struct s_var	*next;
}					t_var;

typedef enum s_var_state
{
	SHELL,
	ENV,
}					t_var_state;

void				get_envlist(t_var **list);
t_var				*get_new_var(int i, char **environ);
void				add_last_newvar(t_var *first, t_var *new);

// error.h
void				fatal_error(const char *msg) __attribute__((noreturn));
void				handle_malloc_error(void);
void				quote_error(void);
void				put_error_message(char *argv, char *message);

// support.h
char				*ft_strjoinendl(char const *s1, char const *s2);
size_t				ft_strlen_nocrash(const char *s);

#endif