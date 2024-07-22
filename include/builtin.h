#ifndef BUILTIN_H
# define BUILTIN_H

void	exec_env(char **argv, t_var **list);
void	exec_unset(char **argv, t_var **list);
void	exec_pwd(t_var **list);
void	exec_cd(char **argv, t_var **list);
void	exec_cd(char **argv, t_var **list);
void    exec_export(t_var    **list, char **argv);
char	*ft_getenv(t_var **list, char *key_name);
int		ft_argvlen(char **argv);
#endif