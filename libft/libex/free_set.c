#include "libex.h"
#include <stdlib.h>

void	free_set(void **dst, void *src)
{
	free(*dst);
	*dst = src;
}
