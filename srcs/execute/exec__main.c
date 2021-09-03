#include "shell.h"

#include "astree.h"
#include "exec.h"

void	minishell_execute(t_astree *tree)
{
	int	status;

	status = 0;
	execute_cmdline(tree, &status);
}
