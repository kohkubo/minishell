#ifndef SHELL_H
# define SHELL_H
# include "../libft/libft/libft.h"
# include "../libft/libex/libex.h"
# include <stdio.h>
char	**get_reserved(char *reserved[8]);
void	parse(char *input);
#endif
