#include "shell.h"

typedef int			(*t_reserved_func)(char **arg);
char				*g_reserved_words[] = {
	"echo", "cd", "pwd", "export", "unset", "env", "exit", NULL
};
t_reserved_func		g_reserved_funcs[] = {
	ft_echo, NULL, NULL, NULL, NULL, ft_env, ft_exit, NULL
};

static void	not_implemented(char *word)
{
	ft_putstr_fd(word, 1);
	ft_putendl_fd(" is not implemented yet", 1);
}

void	parse(char *input)
{
	char	**buf;
	int		i;

	buf = ft_split(input, ' ');
	if (buf == NULL)
		exit(1);
	if (buf[0] != NULL)
		i = contain(g_reserved_words, buf[0]);
	if (buf[0] != NULL && i != -1)
	{
		if (g_reserved_funcs[i] != NULL)
			g_reserved_funcs[i](&buf[1]);
		else
			not_implemented(buf[0]);
	}
	else
	{
		i = 0;
		while (buf[i])
			ft_putendl_fd(buf[i++], 1);
	}
	buf = free_string_array(buf);
}
