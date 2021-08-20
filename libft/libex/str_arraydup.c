#include "libex.h"

char	**str_arraydup(char **array)
{
	int		i;
	char	**ss;
	char	**head;

	ss = ft_xmalloc(sizeof(char *) * (arraylen(array) + 1));
	head = ss;
	i = 0;
	while (array[i])
	{
		ss[i] = ft_xstrdup(array[i]);
		i++;
	}
	ss[i] = NULL;
	return (head);
}
