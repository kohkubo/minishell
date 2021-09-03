#include "libex.h"

int	catch_error(int status, char *title)
{
	if (status == -1)
	{
		perror(title);
		exit(1);
	}
	return (status);
}

void	*catch_null(void *ptr, char *title)
{
	if (ptr == NULL)
	{
		perror(title);
		exit(1);
	}
	return (ptr);
}
