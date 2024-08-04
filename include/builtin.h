/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyoshimi <nyoshimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 14:05:38 by ktsukamo          #+#    #+#             */
/*   Updated: 2024/08/04 12:50:06 by nyoshimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

int		exec_builtin(char **argv, t_var **list, t_tool *tool, int count);
int	exec_builtin_based_on_pipe(char **argv, t_var **list, t_tool *tool, int count);
void	exec_echo(char **argv);
void	exec_env(char **argv, t_var **list);
void	exec_exit(char **argv, int *status, t_tool *tool);
void	exec_unset(char **argv, t_var **list);
void	exec_pwd(t_var **list, char *pwd);
void	exec_cd(char **argv, t_var **list, t_tool *tool);
void	exec_export(t_var **list, char **argv, int count);
char	*ft_getenv(t_var **list, char *key_name);
int		ft_argvlen(char **argv);
void	save_oldpwd(t_var **list, char *tmp);
void	save_tool_pwd(t_tool *tool, char *tmp2, char *path);
void	init_oldpwd(t_tool *tool, t_var **list, char *tmp2, char *path);
char	*get_value(char *arg);
int		get_env_keyname(char *arg, char **key_name);
void	ft_getenv_node(t_var **list, char *key_name, t_var **opt);
void	put_export_error(char *arg);
void	export_arg(char *arg, t_var **list);
t_var	*export_new_var(char *newkey, char *newvalue);
void	sort_and_put_env(t_var **list);
void	put_env(t_var *save);

#endif