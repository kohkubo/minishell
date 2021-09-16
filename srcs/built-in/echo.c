#include "shell.h"

static void	ft_echo_exit_check(char **args)
{
	if (*args == NULL)
	{
		printf("\n");
		exit(0);
	}
}

int	ft_echo(char **args)
{
	bool	op_flg;

	op_flg = false;
	if (args == NULL)
		return (1);
	ft_echo_exit_check(args);
	if (!ft_strncmp(*args, "-", -1))
		ft_echo_exit_check(++args);
	else if (!ft_strncmp(*args, "-n", -1))
	{
		op_flg = true;
		if (*++args == NULL)
			return (0);
	}
	printf("%s", *args++);
	while (*args)
	{
		printf(" %s", *args);
		args++;
	}
	if (op_flg == false)
		printf("\n");
	return (0);
}
