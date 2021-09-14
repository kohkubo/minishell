#include "libex.h"

char	*ft_strchrset(const char *s, char *charset)
{
	int	i;

	while (*s)
	{
		i = 0;
		while (charset[i])
		{
			if (*s == charset[i])
				return ((char *)s);
			i++;
		}
		s++;
	}
	return (NULL);
}
