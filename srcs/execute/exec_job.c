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

int	pipexec(t_astree *tree)
{
	pid_t	pid;
	int		pipefd[2];

	catch_error(pipe(pipefd), "pipe");
	pid = catch_error(fork(), "fork");
	if (pid == CHILD)
	{
		connect_pipe(pipefd, STDOUT_FILENO);
		execute_cmd(tree->left);
	}
	pid = catch_error(fork(), "fork");
	if (pid == CHILD)
	{
		connect_pipe(pipefd, STDIN_FILENO);
		execute_cmd(tree->right);
	}
	catch_error(close(pipefd[0]), "close");
	catch_error(close(pipefd[1]), "close");
	return (pid);
}

enum e_mean
{
	_,
	LAST,
	LEN
};

/*
** <job>			::= <command> '|' <job>
**					  | <command>
*/
void	execute_job(t_astree *tree, int *status)
{
	t_node_type	type;
	pid_t		pid[2];
	int			child_status;

	type = tree->type & ~NODE_DATA;
	if (type == NODE_PIPE)
	{
		pid[LAST] = pipexec(tree);
	}
	else
	{
		pid[LAST] = catch_error(fork(), "fork");
		if (pid[LAST] == CHILD)
			execute_cmd(tree);
	}
	pid[_] = 0;
	while (pid[_] >= 0)
	{
		pid[_] = waitpid(-1, &child_status, 0);
		if (pid[_] == pid[LAST])
			*status = child_status;
	}
	if (errno != ECHILD)
		pexit("minishell", 1);
}
