#include "libex.h"

void	pexit(char *message, int status)
{
	perror(message);
	exit(status);
}

int	catch_error(int status, char *title)
{
	if (status == -1)
		pexit(title, 1);
	return (status);
}

void	*catch_null(void *ptr, char *title)
{
	if (ptr == NULL)
		pexit(title, 1);
	return (ptr);
}
