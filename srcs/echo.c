#include "../includes/shell.h"
#include "../libft/libft/libft.h"

static int	va_arg_null_valid(va_list ap, char **arg)
{
	*arg = va_arg(ap, char *);
	return (!*arg);
}

static int	print_echo(va_list ap, char **arg, int n)
{
	printf("%s", *arg);
	while (--n > 0)
	{
		if (va_arg_null_valid(ap, arg))
			return (1);
		printf(" %s", *arg);
	}
	return (0);
}

static int	ft_echo_do(va_list ap, int n)
{
	int		op_flg;
	char	*arg;

	op_flg = 0;
	if (n > 0)
	{
		if (va_arg_null_valid(ap, &arg))
			return (1);
		if (!ft_strncmp(arg, "-n", __SIZE_MAX__))
		{
			op_flg++;
			if (--n == 0)
				return (0);
			if (va_arg_null_valid(ap, &arg))
				return (1);
		}
		if (print_echo(ap, &arg, n))
			return (1);
	}
	if (!op_flg)
		printf("\n");
	return (0);
}

int	ft_echo(int n, ...)
{
	va_list	ap;
	int		ret;

	va_start(ap, n);
	ret = ft_echo_do(ap, n);
	va_end(ap);
	return (ret);
}
