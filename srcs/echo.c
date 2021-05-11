#include "../includes/shell.h"
#include "../libft/libft/libft.h"

static int	ft_echo_do(va_list ap, int n)
{
	int		op_flg;
	char	*arg;

	op_flg = 0;
	if (n > 0)
	{
		arg = va_arg(ap, char *);
		if (!arg)
			arg = "(null)";
		else if (!ft_strncmp(arg, "-n", __SIZE_MAX__))
		{
			op_flg++;
			if (--n == 0)
				return (0);
			arg = va_arg(ap, char *);
		}
		printf("%s", arg);
		while (--n > 0)
			printf(" %s", va_arg(ap, char *));
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
	return (0);
}
