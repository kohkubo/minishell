#include "shell.h"

int	ft_echo(char **args)
{
	bool	op_flg;

	op_flg = false;
	if (args == NULL)
		return (1);
	if (*args == NULL)
	{
		ft_putstr_fd("\n", 1);
		return (0);
	}
	while (!ft_strncmp(*args, "-n", SIZE_MAX))
	{
		op_flg = true;
		if (*++args == NULL)
			return (0);
	}
	ft_putstr_fd(*args++, 1);
	while (*args)
	{
		ft_putstr_fd(" ", 1);
		ft_putstr_fd(*args++, 1);
	}
	if (op_flg == false)
		ft_putstr_fd("\n", 1);
	return (0);
}
