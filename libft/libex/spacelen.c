#include "libex.h"

size_t	spacelen(char *s)
{
	size_t	i;

	i = 0;
	while (ft_isspace(s[i]))
		i++;
	return (i);
}
