#include "exec.h"

#include "astree.h"
#include "libft.h"

/**
 * <command>	::= <simple command> <redirection list>
 *				  | <simple command>
 */
void	execute_cmd(t_astree *tree, int *status)
{
	t_node_type	type;

	type = tree->type & ~NODE_DATA;
	if (type == NODE_REDIRECTION)
	{
		ft_putendl_fd("not support yet.", 1);
	}
	else
	{
		execute_simplecmd(tree, status);
	}
}
