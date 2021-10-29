#include "exec.h"

#include "astree.h"

enum e_mean
{
	_,
	LAST,
	STDIN_BACKUP,
	LEN
};

/*
** <command line>	::= <job> ';' <command line>	// ignore
**					  | <job> ';'					// ignore
**					  | <job> '&' <command line>	// ignore
**					  | <job> '&'					// ignore
**					  | <job>
*/
void	execute_cmdline(t_astree *tree, int *status)
{
	if (!(tree->type & NODE_AND) && !(tree->type & NODE_OR))
		return ((void)execute_job(tree, status));
	if (tree->type & NODE_AND)
	{
		execute_job(tree->left, status);
		if (get_status(*status) == 0)
			execute_job(tree->right, status);
	}
	else if (tree->type & NODE_OR)
	{
		execute_job(tree->left, status);
		if (get_status(*status) != 0)
			execute_job(tree->right, status);
	}
}
