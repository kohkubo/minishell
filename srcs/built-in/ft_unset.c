#include "shell.h"

int	ft_unset(char **args)
{
	while (*args)
	{
		hash_remove(g_shell.env, *args);
		args++;
	}
	return (0);
}
