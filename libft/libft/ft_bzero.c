#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	while (0 < n--)
		*(char *)s++ = '\0';
}
