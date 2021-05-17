#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dlen;
	size_t	slen;

	dlen = ft_strlen(dst);
	slen = ft_strlen(src);
	if (dstsize <= dlen)
		return (slen + dstsize);
	dst += dlen;
	while (*src && dlen < dstsize-- - 1)
		*dst++ = *src++;
	*dst = '\0';
	return (dlen + slen);
}
