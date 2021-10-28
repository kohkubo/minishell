#include "shell.h"

#include <sys/wait.h>
#include <stdlib.h>
#include "astree.h"
#include "exec.h"

int	get_status(int	status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (WTERMSIG(status) + 128);
	else if (WIFSTOPPED(status))
		return (WSTOPSIG(status));
	else
		return (EXIT_FAILURE);
}

int	minishell_execute(t_astree *tree)
{
	int	status;

	status = 0;
	execute_cmdline(tree, &status);
	return (get_status(status));
}
