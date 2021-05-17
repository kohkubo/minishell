#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*d;
	unsigned char	*s;

	d = (unsigned char *)dst;
	s = (unsigned char *)src;
	if (s < d)
	{
		s += len - 1;
		d += len - 1;
		while (0 < len--)
			*d-- = *s--;
	}
	else if (d < s)
		while (0 < len--)
			*d++ = *s++;
	return (dst);
}
