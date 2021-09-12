#include "libft.h"
#include "libex.h"
#include "libhash.h"
#include <libc.h>

int	catch_error(int state)
{
	if (state)
	{
		ft_putstr_fd("FAILURE\n", 2);
		exit(1);
	}
	return (0);
}
