#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	while (0 < n && *(const unsigned char *)s != (unsigned char)c)
	{
		--n;
		++s;
	}
	if (n)
		return ((void *)s);
	else
		return (NULL);
}
