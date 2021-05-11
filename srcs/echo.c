#include "../includes/shell.h"
#include "../libft/libft/libft.h"

static void	print_n(int flg)
{
	if (flg)
		printf("\n");
}

int	ft_echo(int n, ...)
{
	va_list	ap;
	int		op_flg;
	char	*arg;

	va_start(ap, n);
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
	print_n(!op_flg);
	va_end(ap);
	return (0);
}
