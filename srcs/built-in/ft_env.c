#include "shell.h"

static void	print_env_array(char **array)
{
	while (*array)
	{
		if (ft_strchr(*array, '=') != NULL)
			printf("%s\n", *array);
		array++;
	}
}

int	ft_env(char **args)
{
	char			**env;
	char			**tmp;
	t_hash_table	*env_hash;

	tmp = hash_getall(g_shell.env, NULL);
	env_hash = hash_create_table(1024);
	store_shellenv(tmp, env_hash);
	store_shellenv(args, env_hash);
	env = hash_getall(env_hash, NULL);
	print_env_array(env);
	free_string_array(env);
	free_string_array(tmp);
	hash_clear_table(&env_hash);
	return (0);
}
