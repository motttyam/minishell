/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyoshimi <nyoshimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 14:05:16 by ktsukamo          #+#    #+#             */
/*   Updated: 2024/07/30 23:11:06 by nyoshimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

// tool
typedef struct s_tool
{
	int							status;
	char						*home;
	char						*pwd;
	char						*input;
	int 						syntax_status;
	char						pwd_first[PATH_MAX];
}								t_tool;

// fd.c
typedef struct s_fd
{
	int				saved_stdin;
	int				saved_stdout;
	int				saved_stderr;
}					t_fd;

void							save_fd(t_fd *saved_fd);
void							reinit_fd(t_fd saved_fd);
void							close_fd(t_fd saved_fd);

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
int					ft_isspace(int c);

#endif