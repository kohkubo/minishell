#include "libdebug.h"

int	arraylen(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

void	display_array(char **array)
{
	while (*array)
		printf("%s\n", *array++);
}

void	array_cmp(char **aa, char **bb)
{
	int	i;

	i = 0;
	while (aa[i] && bb[i])
	{
		if (ft_strcmp(aa[i], bb[i]))
		{
			printf("%s : %s\n", aa[i], bb[i]);
			exit(1);
		}
		i++;
	}
}

char	**str_array_dup(char **array)
{
	int		i;
	char	**ss;
	char	**head;

	ss = calloc(sizeof(char *), arraylen(array) + 1);
	head = ss;
	i = 0;
	while (array[i])
	{
		ss[i] = ft_strdup(array[i]);
		i++;
	}
	ss[i] = 0;
	return (head);
}
