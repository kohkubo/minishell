#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	bufsize;
	char	*buf;
	size_t	len1;
	size_t	len2;

	bufsize = ft_strlen(s1) + ft_strlen(s2) + 1;
	buf = (char *)malloc(bufsize * sizeof(char));
	if (buf == NULL)
		return (NULL);
	len1 = 0;
	while (s1 != NULL && *s1)
		buf[len1++] = *s1++;
	len2 = 0;
	while (s2 != NULL && *s2)
		buf[len1 + len2++] = *s2++;
	buf[len1 + len2] = '\0';
	return (buf);
}
