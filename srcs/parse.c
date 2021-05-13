#include "shell.h"

char	**get_reserved(char *reserved[8])
{
	reserved[0] = "echo";
	reserved[1] = "cd";
	reserved[2] = "pwd";
	reserved[3] = "export";
	reserved[4] = "unset";
	reserved[5] = "env";
	reserved[6] = "exit";
	reserved[7] = NULL;
	return (reserved);
}

void	parse(char *input)
{
	char	**buf;
	char	*reserved[8];
	int		i;

	buf = ft_split(input, ' ');
	if (buf[0] != NULL && is_contain(get_reserved(reserved), buf[0]) != -1)
	{
		ft_putstr_fd(buf[0], 1);
		ft_putendl_fd(" is not implemented yet", 1);
		return ;
	}
	i = 0;
	while (buf[i])
	{
		ft_putendl_fd(buf[i], 1);
		i++;
	}
}
