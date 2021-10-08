#include "exec.h"

#include <fcntl.h>
#include <unistd.h>
#include "libft.h"
#include "libex.h"
#include "astree.h"

int	handle_open_error(char *filename, bool is_builtin)
{
	if (!is_builtin)
		minishell_pexit(filename, 1);
	minishell_perror(filename, 1);
	return (1);
}

int	redirect_in(char *filename, bool is_builtin)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (handle_open_error(filename, is_builtin));
	catch_error(dup2(fd, STDIN_FILENO), "dup2");
	catch_error(close(fd), "close");
	return (0);
}

enum e_mode
{
	OVERWRITE,
	APPEND,
};

int	redirect_out(char *filename, enum e_mode mode, bool is_builtin)
{
	int	fd;
	int	option;

	option = O_WRONLY | O_CREAT;
	if (mode == OVERWRITE)
		option |= O_TRUNC;
	else if (mode == APPEND)
		option |= O_APPEND;
	fd = open(filename, option, 0644);
	if (fd == -1)
		return (handle_open_error(filename, is_builtin));
	catch_error(dup2(fd, STDOUT_FILENO), "dup2");
	catch_error(close(fd), "close");
	return (0);
}

void	redirect_heredoc(char *data)
{
	int		pipefd[2];
	pid_t	pid;

	catch_error(pipe(pipefd), "pipe");
	pid = catch_error(fork(), "fork");
	if (pid == 0)
	{
		connect_pipe(pipefd, STDOUT_FILENO);
		catch_error(write(STDOUT_FILENO, data, ft_strlen(data)), "write");
		exit(0);
	}
	catch_error(waitpid(pid, NULL, 0), "waitpid");
	connect_pipe(pipefd, STDIN_FILENO);
}

/**
 * <redirection list>	::= <redirection> <redirection list>
 * <redirection>		::= '<' <filename> <token list>
 *						  | '>' <filename> <token list>
 *						  | '<<' <filename> <token list>
 *						  | '>>' <filename> <token list>
 */
int	execute_redirection(t_astree *tree, bool is_builtin)
{
	while (tree && tree->type & NODE_REDIRECT_LIST)
	{
		if (tree->left->type & NODE_REDIRECT_IN)
		{
			if (redirect_in(tree->left->data, is_builtin))
				return (1);
		}
		else if (tree->left->type & NODE_REDIRECT_OUT)
		{
			if (redirect_out(tree->left->data, OVERWRITE, is_builtin))
				return (1);
		}
		else if (tree->left->type & NODE_REDIRECT_OUT2)
		{
			if (redirect_out(tree->left->data, APPEND, is_builtin))
				return (1);
		}
		else if (tree->left->type & NODE_REDIRECT_IN2)
			redirect_heredoc(tree->left->data);
		tree = tree->right;
	}
	return (0);
}
