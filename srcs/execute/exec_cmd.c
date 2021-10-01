#include "exec.h"

#include "astree.h"

/**
 * <command>	::= <simple command> <redirection list>
 *				  | <simple command>
 */
int	execute_cmd(t_astree *tree)
{
	if (tree->type & NODE_REDIRECTION)
	{
		execute_redirection(tree->right);
		return (execute_simplecmd(tree->left));
	}
	else
	{
		return (execute_simplecmd(tree));
	}
}
