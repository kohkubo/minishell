#include "shell.h"

void	is_not_numeric_exit(char *arg)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putendl_fd(": numeric argument required", 2);
	exit(255);
}

int	ft_exit(char **args)
{
	long	num;

	errno = 0;
	if (arraylen(args) > 1)
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		return (1);
	}
	ft_putendl_fd("exit", 1);
	if (args[0] == NULL)
		exit(g_shell.exit_status);
	if (!is_num_string(args[0]))
		is_not_numeric_exit(args[0]);
	num = ft_atol(args[0]);
	if (errno == EINVAL)
		is_not_numeric_exit(args[0]);
	exit((int)num);
	return (0);
}
