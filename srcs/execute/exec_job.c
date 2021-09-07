#include "exec.h"

#include "astree.h"
#include "libft.h"

/*
** <job>			::= <command> '|' <job>
**					  | <command>
*/
#include <stdio.h>
void	execute_job(t_astree *tree, int *status)
{
	t_node_type	type;

	type = tree->type & ~NODE_DATA;
	if (type == NODE_PIPE)
	{
		ft_putendl_fd("not support yet.", 1);
	}
	else
	{
		execute_cmd(tree, status);
	}
}
