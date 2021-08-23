#include "shell.h"

extern t_shell	g_shell;

int	ft_env(char **args)
{
	char	**env;
	char	**tmp;
	t_hash_table *env_hash;

	tmp = hash_getall(g_shell.env);
	env_hash = hash_create_table(1024);
	store_shellenv(tmp, env_hash);
	store_shellenv(args, env_hash);
	env = hash_getall(env_hash);
	print_array(env);
	free_string_array(env);
	free_string_array(tmp);
	hash_clear_table(&env_hash);
	return (0);
}
