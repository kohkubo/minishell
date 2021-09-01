#include "shell.h"

static char	*dict_fmt_value_null(char *key)
{
	char	*s;

	s = ft_xmalloc(ft_strlen(key) + 1);
	ft_strlcpy(s, key, SIZE_MAX);
	return (s);
}

static char	*dict_fmt_export(char *key, char *value)
{
	char	*s;

	if (value == NULL)
		return (dict_fmt_value_null(key));
	s = ft_xmalloc(ft_strlen(key) + ft_strlen(value) + 4);
	ft_strlcpy(s, key, SIZE_MAX);
	ft_strlcat(s, "=\"", SIZE_MAX);
	ft_strlcat(s, value, SIZE_MAX);
	ft_strlcat(s, "\"", SIZE_MAX);
	return (s);
}

static void	print_export_array(char **array)
{
	while (*array)
	{
		printf("declare -x ");
		printf("%s\n", *array++);
	}
}

int	ft_export(char **args)
{
	char	**env;

	if (!args[0])
	{
		env = hash_getall(g_shell.env, dict_fmt_export);
		print_export_array(env);
		free_string_array(env);
	}
	else
	{
		store_shellenv(args, g_shell.env);
	}
	return (0);
}
