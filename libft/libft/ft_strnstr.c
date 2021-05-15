#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	char	c;
	char	sc;
	size_t	i;

	c = *needle++;
	if (c != '\0')
	{
		i = ft_strlen(needle);
		while (1)
		{
			while (1)
			{
				sc = *haystack++;
				if (len-- < 1 || sc == '\0')
					return (NULL);
				if (sc == c)
					break ;
			}
			if (len < i)
				return (NULL);
			if (ft_strncmp(haystack, needle, i) == 0)
				break ;
		}
	}
	return ((char *)--haystack);
}
