#include "shell.h"

#include <errno.h>

void	store_shellenv(char **arr, t_hash_table *table)
{
	char		*tmp;
	size_t		i;

	i = 0;
	while (arr[i] != NULL)
	{
		if (ft_strchr(arr[i], '=') != NULL)
		{
			tmp = ft_strdup(arr[i]);
			tmp[ft_strchr(tmp, '=') - tmp] = '\0';
			hash_setstr(table, tmp, tmp + ft_strlen(tmp) + 1);
			free_set((void **)&tmp, NULL);
		}
		else
		{
			if (hash_getstr(table, arr[i]) == NULL)
				hash_setstr(table, arr[i], NULL);
		}
		i++;
	}
}

static void	env_init(void)
{
	extern char	**environ;

	store_shellenv(environ, g_shell.env);
	hash_remove(g_shell.env, "OLDPWD");
	hash_setstr(g_shell.env, "OLDPWD", NULL);
	g_shell.pwd = getcwd(NULL, 0);
}

void	minishell_init(void)
{
	errno = 0;
	g_shell.env = hash_create_table(1024);
	signal_init();
	env_init();
}
