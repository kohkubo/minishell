#include "libdebug.h"

static int	compare(const void *a, const void *b)
{
	return ft_strcmp(*(const char **)a, *(const char **)b);
}

void	qsort_strarray(char **array)
{
	qsort(array, arraylen(array), sizeof(char *), compare);
}
