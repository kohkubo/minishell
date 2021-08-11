#include "libex.h"

void	ft_error_exit(const char *emsg)
{
	ft_putendl_fd((char *)emsg, 2);
	exit(1);
}
