#ifndef SHELL_H
# define SHELL_H
# include "../libft/libft/libft.h"
# include "../libft/libex/libex.h"
# include <stdio.h>
# include <stdbool.h>
int		ft_echo(char **args);
int		ft_exit(char **arg);
void	parse(char *input);
#endif
