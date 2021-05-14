#include "shell.h"

typedef int			(*t_reserved_func)(char **arg);
char				*g_reserved_words[] = {
	"echo", "cd", "pwd", "export", "unset", "env", "exit", NULL
};
t_reserved_func		g_reserved_funcs[] = {
	NULL, NULL, NULL, NULL, NULL, NULL, ft_exit, NULL
};

void	parse(char *input)
{
	char	**buf;
	int		i;

	buf = ft_split(input, ' ');
	i = is_contain(g_reserved_words, buf[0]);
	if (buf[0] != NULL && i != -1)
	{
		if (g_reserved_funcs[i] != NULL)
			g_reserved_funcs[i](&buf[1]);
		else
		{
			ft_putstr_fd(buf[0], 1);
			ft_putendl_fd(" is not implemented yet", 1);
		}
		return ;
	}
	i = 0;
	while (buf[i])
	{
		ft_putendl_fd(buf[i], 1);
		i++;
	}
}
