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

/*
** <job>			::= <command> '|' <job>
**					  | <command>
*/
void	execute_job(t_astree *tree, int *status, pid_t *pid)
{
	int		pipefd[2];

	if (tree->type & NODE_PIPE)
	{
		catch_error(pipe(pipefd), "pipe");
		*pid = catch_error(fork(), "fork");
		if (*pid == CHILD)
		{
			connect_pipe(pipefd, STDOUT_FILENO);
			exit(execute_cmd(tree->left));
		}
		connect_pipe(pipefd, STDIN_FILENO);
		execute_job(tree->right, status, pid);
	}
	else
	{
		if (*pid == NO_PIPE && is_builtin(tree))
			return ((void)(*status = execute_cmd(tree)));
		*pid = catch_error(fork(), "fork");
		if (*pid == CHILD)
		{
			exit(execute_cmd(tree));
			catch_error(close(STDIN_FILENO), "close");
		}
	}
}
