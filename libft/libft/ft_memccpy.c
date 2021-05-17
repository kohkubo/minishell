#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	uc;
	unsigned char	*d;
	unsigned char	*s;

	uc = (unsigned char)c;
	d = (unsigned char *)dst;
	s = (unsigned char *)src;
	while (0 < n--)
	{
		*d = *s;
		if (*d == uc)
			return ((void *)(d + 1));
		d++;
		s++;
	}
	return (NULL);
}
