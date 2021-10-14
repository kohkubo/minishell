#include "exec.h"

#include "astree.h"

/**
 * <command>	::= <simple command> <redirection list>
 *				  | <simple command>
 */
int	execute_cmd(t_astree *tree, bool is_builtin)
{
	if (tree->type & NODE_REDIRECTION)
	{
		if (execute_redirection(tree->right, is_builtin))
			return (1);
		return (execute_simplecmd(tree->left));
	}
	else
	{
		return (execute_simplecmd(tree));
	}
}
