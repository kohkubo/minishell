#include "exec.h"

#include <sys/wait.h>
#include <errno.h>
#include "libft.h"
#include "libex.h"
#include "astree.h"
#include "minishell_signal.h"

#define CHILD	(0)

enum e_mean
{
	_,
	LAST,
	STDIN_BACKUP,
	LEN
};

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

void	do_job(t_astree *tree, int *status, pid_t *pid)
{
	if (tree->type & NODE_PIPE)
	{
		*pid = pipexec(tree->left);
		do_job(tree->right, status, pid);
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

/*
** <job>			::= <command> '|' <job>
**					  | <command>
*/
void	execute_job(t_astree *tree, int *status)
{
	pid_t	pid[LEN];
	int		backup_fd[2];
	int		child_status;

	pid[_] = 0;
	pid[LAST] = -1;
	backup_fd[STDIN_FILENO] = catch_error(dup(STDIN_FILENO), "dup");
	backup_fd[STDOUT_FILENO] = catch_error(dup(STDOUT_FILENO), "dup");
	signal_init(signal_child_process, signal_child_process, NULL);
	do_job(tree, status, &pid[LAST]);
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
	signal_init(signal_handler_prompt, SIG_IGN, NULL);
}
