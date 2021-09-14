#include "libex.h"

void	pexit(char *message)
{
	perror(message);
	exit(1);
}

int	catch_error(int status, char *title)
{
	if (status == -1)
		pexit(title);
	return (status);
}

void	*catch_null(void *ptr, char *title)
{
	if (ptr == NULL)
		pexit(title);
	return (ptr);
}
