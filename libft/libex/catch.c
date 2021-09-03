#include "libex.h"

int	catch_error(int status, char *title)
{
	if (status == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(title);
		exit(1);
	}
	return (status);
}

void	*catch_null(void *ptr, char *title)
{
	if (ptr == NULL)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(title);
		exit(1);
	}
	return (ptr);
}
