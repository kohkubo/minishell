#include "exec.h"

#include "astree.h"
#include <sys/wait.h>
#include <errno.h>
#include "libex.h"

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
	pid_t	pid[LEN];
	int		child_status;

	pid[_] = 0;
	pid[LAST] = -1;
	pid[STDIN_BACKUP] = catch_error(dup(STDIN_FILENO), "dup");
	execute_job(tree, status, &pid[LAST]);
	dup2(pid[STDIN_BACKUP], STDIN_FILENO);
	while (pid[_] >= 0)
	{
		pid[_] = waitpid(-1, &child_status, 0);
		if (pid[_] != -1 && pid[_] == pid[LAST])
			*status = child_status;
	}
	if (errno != ECHILD)
		pexit("minishell");
}
