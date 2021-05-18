#include <stdio.h>
#include <libc.h>
#include "./../../../includes/shell.h"

int	main(int ac, char **av)
{
	return (ft_echo(&av[1]));
}
