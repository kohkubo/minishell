#include "libex.h"

static void	strswap(char **a, char **b)
{
	char	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	strsort(char *str[], int n)
{
	int	i;
	int	j;

	i = 0;
	while (i < n)
	{
		j = i + 1;
		while (j < n)
		{
			if ((ft_strcmp(str[j], str[i])) < 0)
				strswap(&str[i], &str[j]);
			j++;
		}
		i++;
	}
}
