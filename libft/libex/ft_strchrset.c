#include "libex.h"

char	*ft_strchrset(const char *s, char *charset)
{
	while (*s)
	{
		if (ft_strchr(charset, *s))
			return ((char *)s);
		s++;
	}
	return (NULL);
}
