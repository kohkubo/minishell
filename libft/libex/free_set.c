#include "libex.h"

void	free_set(void **dst, void *src)
{
	free(*dst);
	*dst = src;
}
