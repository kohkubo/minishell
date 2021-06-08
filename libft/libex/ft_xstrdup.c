#include "libex.h"

char	*ft_xstrdup(const char *s1)
{
	char	*dst;

	dst = ft_xmalloc(ft_strlen(s1) + 1);
	ft_strlcpy(dst, s1, ULLONG_MAX);
	return (dst);
}
