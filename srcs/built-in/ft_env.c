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
	char	**env;

	(void)args;
	env = hash_getall(g_shell.env, NULL);
	print_env_array(env);
	free_string_array(env);
	return (0);
}
