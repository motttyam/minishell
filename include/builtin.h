#ifndef BUILTIN_H
# define BUILTIN_H

#include <sys/stat.h>
#include <sys/types.h>

void	ft_getenv_node(t_var **list, char *key_name, t_var **opt);

int		exec_builtin(char **argv, t_var **list, t_tool *tool);
void	exec_echo(char **argv);
void	exec_env(char **argv, t_var **list);
void	exec_exit(char **argv, int *status);
void	exec_unset(char **argv, t_var **list);
void	exec_pwd(t_var **list, char *pwd);
void	exec_cd(char **argv, t_var **list, t_tool *tool);
void	exec_export(t_var **list, char **argv);
char	*ft_getenv(t_var **list, char *key_name);
int		ft_argvlen(char **argv);
#endif