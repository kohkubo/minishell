#include "libex.h"

void	*ft_xmalloc(size_t size)
{
	void	*ptr;

	if (size == 0)
		exit(1);
	ptr = malloc(size);
	if (ptr == NULL)
		exit(1);
	return (ptr);
}
