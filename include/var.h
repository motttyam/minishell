/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyoshimi <nyoshimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 13:59:31 by nyoshimi          #+#    #+#             */
/*   Updated: 2024/07/20 21:14:01 by nyoshimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VAR_H
# define VAR_H

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

void	get_envlist(t_var **list);
t_var	*get_new_var(int i, char **environ);
void	add_last_newvar(t_var *first, t_var *new);

#endif