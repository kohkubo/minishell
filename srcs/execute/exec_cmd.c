#include "exec.h"

#include "astree.h"
#include "libft.h"

/**
 * <command>	::= <simple command> <redirection list>
 *				  | <simple command>
 */
int	execute_cmd(t_astree *tree)
{
	if (tree->type & NODE_REDIRECTION)
	{
		ft_putendl_fd("not support yet.", 1);
		return (1);
	}
	else
	{
		return (execute_simplecmd(tree));
	}
}
