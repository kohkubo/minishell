#include "libft.h"

static char	**free_all(char **buf)
{
	size_t	i;

	i = 0;
	while (buf[i])
	{
		free(buf[i]);
		buf[i] = NULL;
		i++;
	}
	free(buf);
	return (NULL);
}

char	**cut_word(char const *s, char c, char **buf)
{
	const char	*ptr;
	size_t		len;
	size_t		i;

	i = 0;
	while (buf != NULL && *s)
	{
		ptr = ft_strchr(s, c);
		if (ptr == NULL)
			ptr = s + ft_strlen(s);
		len = ptr - s;
		if (len > 0)
		{
			buf[i] = ft_substr(s, 0, len);
			if (buf[i++] == NULL)
				buf = free_all(buf);
		}
		s += len + (s[len] != '\0');
	}
	buf[i] = NULL;
	return (buf);
}

char	**ft_split(char const *s, char c)
{
	char		**buf;
	const char	*ptr;
	size_t		i;

	if (s == NULL)
		return (NULL);
	ptr = s;
	i = 1;
	while (*ptr)
		if (*ptr++ != c && (*ptr == c || *ptr == '\0'))
			i++;
	buf = (char **)malloc(sizeof(char *) * i);
	if (!buf)
		return (NULL);
	return (cut_word(s, c, buf));
}
