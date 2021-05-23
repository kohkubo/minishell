#include "libex.h"

static void	ft_fatalx(const char *emsg)
{
	errno = 0;
	ft_fatal(emsg);
}

void	*ft_xmalloc(size_t size)
{
	void	*ptr;

	if (size == 0)
		ft_fatalx("xmalloc: zero size");
	ptr = malloc(size);
	if (ptr == NULL)
		ft_fatal("xmalloc: ");
	return (ptr);
}
