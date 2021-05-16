#include "../../includes/shell.h"

int	ft_echo(char **args)
{
	int		op_flg;

	op_flg = 0;
	if (!args)
		return (1);
	if (!*args)
	{
		printf("\n");
		exit(0);
	}
	if (!ft_strncmp(*args, "-n", SIZE_MAX))
	{
		op_flg++;
		if (*++args == NULL)
			return (0);
	}
	printf("%s", *args++);
	while (*args)
	{
		printf(" %s", *args);
		args++;
	}
	if (!op_flg)
		printf("\n");
	return (0);
}
