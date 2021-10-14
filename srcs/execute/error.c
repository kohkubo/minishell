#include "exec.h"

#include <stdio.h>
#include <stdlib.h>
#include "libft.h"

int	command_not_found(char *cmd)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putendl_fd(": command not found", 2);
	return (127);
}

int	minishell_perror(char *cmd, int status)
{
	ft_putstr_fd("minishell: ", 2);
	perror(cmd);
	return (status);
}

int	minishell_pexit(char *cmd, int status)
{
	ft_putstr_fd("minishell: ", 2);
	perror(cmd);
	exit(status);
}
