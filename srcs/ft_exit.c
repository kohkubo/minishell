#include "shell.h"

int	ft_exit(char **arg)
{
	(void)arg;
	ft_putendl_fd("this is exit!", 1);
	return (0);
}
