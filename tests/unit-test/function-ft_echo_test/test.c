#include <stdio.h>
#include "./../../../includes/shell.h"

int	main(void)
{
	ft_echo(1, "aiueo");
	ft_echo(2, "aiueo", "ttttt");
	ft_echo(3, "-n", "aiueo", "ttttt");
	ft_echo(1, "-n");
	ft_echo(1, "");
	ft_echo(2, "-n", "");
	ft_echo(NULL);
	ft_echo(1, NULL);
	ft_echo(2, "test", NULL);
	ft_echo(2, NULL, NULL);
	ft_echo(0);
	return (0);
}
