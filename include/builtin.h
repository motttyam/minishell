/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyoshimi <nyoshimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 14:05:38 by ktsukamo          #+#    #+#             */
/*   Updated: 2024/08/01 08:30:55 by nyoshimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

void	ft_getenv_node(t_var **list, char *key_name, t_var **opt);

int		exec_builtin(char **argv, t_var **list, t_tool *tool, int count);
void	exec_echo(char **argv);
void	exec_env(char **argv, t_var **list);
void	exec_exit(char **argv, int *status, t_tool *tool);
void	exec_unset(char **argv, t_var **list);
void	exec_pwd(t_var **list, char *pwd);
void	exec_cd(char **argv, t_var **list, t_tool *tool);
void	exec_export(t_var **list, char **argv, int count);
char	*ft_getenv(t_var **list, char *key_name);
int		ft_argvlen(char **argv);
#endif