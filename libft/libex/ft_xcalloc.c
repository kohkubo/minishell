#include "libex.h"

static void	ft_fatalx(const char *emsg)
{
	errno = 0;
	ft_fatal(emsg);
}

void	*ft_xcalloc(size_t count, size_t size)
{
	void	*ptr;
	size_t	total;

	total = count * size;
	if (total == 0)
		ft_fatalx("xcalloc: zero size");
	ptr = malloc(total);
	if (ptr == NULL)
		ft_fatal("xcalloc: ");
	ft_bzero(ptr, total);
	return (ptr);
}
