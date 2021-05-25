#ifndef SHELL_H
# define SHELL_H
# include "../libft/libft/libft.h"
# include "../libft/libex/libex.h"
# include "../libft/libhash/libhash.h"
# include <stdio.h>
# include <stdbool.h>

void	parse(char *input);
int		ft_exit(char **arg);
int		ft_echo(char **args);
#endif
