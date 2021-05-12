#include "libex.h"

/*
** Check if the string array contains the string word.
** If it is contain, it returns its index, otherwise it returns -1.
*/
int	is_contain(char **array, char *word)
{
	int	i;

	i = 0;
	while (array[i])
	{
		if (ft_strncmp(array[i], word, ft_strlen(word)) == 0)
			return (i);
		i++;
	}
	return (-1);
}
