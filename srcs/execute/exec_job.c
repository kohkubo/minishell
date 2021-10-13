#include "exec.h"

#include "astree.h"
#include "libft.h"
#include "libex.h"

#define CHILD	(0)

void	connect_pipe(int pipefd[2], int fd)
{
	catch_error(dup2(pipefd[fd], fd), "dup2");
	catch_error(close(pipefd[0]), "close");
	catch_error(close(pipefd[1]), "close");
}

pid_t	pipexec(t_astree *tree)
{
	int		pipefd[2];
	pid_t	pid;

	catch_error(pipe(pipefd), "pipe");
	pid = catch_error(fork(), "fork");
	if (pid == CHILD)
	{
		connect_pipe(pipefd, STDOUT_FILENO);
		exit(execute_cmd(tree, true));
	}
	connect_pipe(pipefd, STDIN_FILENO);
	return (pid);
}

/*
** <job>			::= <command> '|' <job>
**					  | <command>
*/
void	execute_job(t_astree *tree, int *status, pid_t *pid)
{
	if (tree->type & NODE_PIPE)
	{
		*pid = pipexec(tree->left);
		execute_job(tree->right, status, pid);
	}
	else
	{
		if (*pid == -1 && is_builtin(tree))
			*status = execute_cmd(tree, false);
		else
		{
			*pid = catch_error(fork(), "fork");
			if (*pid == CHILD)
				exit(execute_cmd(tree, true));
		}
	}
}
