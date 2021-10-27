#include "exec.h"

/*
** <command line>	::= <job> ';' <command line>	// ignore
**					  | <job> ';'					// ignore
**					  | <job> '&' <command line>	// ignore
**					  | <job> '&'					// ignore
**					  | <job>
*/
void	execute_cmdline(t_astree *tree, int *status)
{
	execute_job(tree, status);
}
