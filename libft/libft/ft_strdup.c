#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*dst;

	dst = malloc(ft_strlen(s1) + 1);
	if (!dst)
		return (NULL);
	ft_strlcpy(dst, s1, ULLONG_MAX);
	return (dst);
}
