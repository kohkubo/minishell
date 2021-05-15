#include "libft.h"

static size_t	ft_min(size_t a, size_t b)
{
	return ((a < b) ? (a) : (b));
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*buf;
	size_t	bufsize;
	size_t	i;

	bufsize = 0;
	if (ft_strlen(s) > start)
		bufsize = ft_min(ft_strlen(s) - start, len);
	buf = (char *)malloc(sizeof(char) * (bufsize + 1));
	if (buf == NULL)
		return (NULL);
	i = 0;
	while (i < bufsize)
	{
		buf[i] = s[start + i];
		i++;
	}
	buf[i] = '\0';
	return (buf);
}
