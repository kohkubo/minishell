#include "shell.h"

int	ft_exit(char **args)
{
	if (args[0] == NULL)
		exit(0);
	if (arraylen(args) != 1)
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		return (1);
	}
	if (!is_num_string(args[0]))
		exit(0);
	exit((int)ft_atol(args[0]));
	return (0);
}
