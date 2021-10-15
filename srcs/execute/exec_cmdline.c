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
	int		backup_fd[2];
	int		child_status;

	pid[_] = 0;
	pid[LAST] = -1;
	backup_fd[STDIN_FILENO] = catch_error(dup(STDIN_FILENO), "dup");
	backup_fd[STDOUT_FILENO] = catch_error(dup(STDOUT_FILENO), "dup");
	execute_job(tree, status, &pid[LAST]);
	dup2(backup_fd[STDIN_FILENO], STDIN_FILENO);
	dup2(backup_fd[STDOUT_FILENO], STDOUT_FILENO);
	while (pid[_] >= 0)
	{
		pid[_] = waitpid(-1, &child_status, 0);
		if (pid[_] != -1 && pid[_] == pid[LAST])
			*status = child_status;
	}
	if (errno != ECHILD)
		pexit("minishell");
	errno = 0;
}
