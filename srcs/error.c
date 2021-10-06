#include "error.h"

#include <stdio.h>
#include <stdlib.h>
#include "libft.h"

void	minishell_pexit(char *message)
{
	ft_putstr_fd("minishell: ", 2);
	perror(message);
	exit(1);
}

int	catch_err(int status, char *title)
{
	if (status == -1)
		minishell_pexit(title);
	return (status);
}

void	*catch_nul(void *ptr, char *title)
{
	if (ptr == NULL)
		minishell_pexit(title);
	return (ptr);
}
