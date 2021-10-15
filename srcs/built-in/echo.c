#include "shell.h"

int	ft_echo(char **args)
{
	bool	op_flg;

	op_flg = false;
	if (args == NULL)
		return (1);
	if (*args == NULL)
	{
		printf("\n");
		return (0);
	}
	if (!ft_strncmp(*args, "-n", SIZE_MAX))
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
