#include "shell.h"

int	ft_pwd(char **args)
{
	(void)args;
	printf("%s\n", g_shell.pwd);
	return (0);
}
