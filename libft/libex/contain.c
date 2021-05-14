#include "libex.h"
/*
** Check if the string array contains the string word.
** If it is contain, returns its index, otherwise returns -1.
*/
int	contain(char **array, char *word)
{
	int	i;

	i = 0;
	while (array[i])
	{
		if (ft_strncmp(array[i], word, SIZE_MAX) == 0)
			return (i);
		i++;
	}
	return (-1);
}
