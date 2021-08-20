#include "shell.h"

extern t_shell	g_shell;

int	ft_env(char **args)
{
	char	**env;

	store_shellenv(args);
	env = hash_getall(g_shell.hash);
	print_array(env);
	free_string_array(env);
	return (0);
}
