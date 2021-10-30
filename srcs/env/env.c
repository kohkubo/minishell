#include "shell.h"

#include <errno.h>

static void	error_store_shellenv(const char *str)
{
	char	*tmp;

	if (ft_strchr(str, '=') != NULL)
	{
		tmp = ft_xstrdup(str);
		tmp[ft_strchr(tmp, '=') - tmp] = '\0';
		ft_putstr_fd("export: not an identifier: ", 2);
		ft_putendl_fd(tmp, 2);
		free_set((void **)&tmp, NULL);
	}
	else
	{
		ft_putstr_fd("export: not an identifier: ", 2);
		ft_putendl_fd((char *)str, 2);
	}
}

void	store_shellenv(char **arr, t_hash_table *table)
{
	char		*tmp;
	size_t		i;

	i = 0;
	while (arr[i] != NULL)
	{
		if (ft_atoi(arr[i]) != 0)
		{
			error_store_shellenv(arr[i]);
			return ;
		}
		if (ft_strchr(arr[i], '=') != NULL)
		{
			tmp = ft_xstrdup(arr[i]);
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
	hash_setstr(g_shell.env, "PWD", g_shell.pwd);
}

void	minishell_init(char **input, t_lexer **lex, t_astree **tree)
{
	errno = 0;
	*input = NULL;
	*lex = NULL;
	*tree = NULL;
	g_shell.env = hash_create_table(1024);
	signal_init(signal_handler_prompt, SIG_IGN, NULL);
	env_init();
}
