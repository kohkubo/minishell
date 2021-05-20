#include "libex.h"

void	ft_fatal(const char *emsg)
{
	ft_putstr_fd("fatal: ", 2);
	if (emsg == NULL)
		ft_putendl_fd(ft_strerror(errno), 2);
	else
	{
		if (errno)
		{
			ft_putstr_fd((char *)emsg, 2);
			ft_putendl_fd(ft_strerror(errno), 2);
		}
		else
			ft_putendl_fd((char *)emsg, 2);
	}
	exit(1);
}
