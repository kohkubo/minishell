#include "exec.h"

#include <fcntl.h>
#include <unistd.h>
#include "libft.h"
#include "libex.h"
#include "astree.h"

void	redirect_in(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	catch_error(fd, filename);
	catch_error(dup2(fd, STDIN_FILENO), "dup2");
	catch_error(close(fd), "close");
}

enum e_mode
{
	OVERWRITE,
	APPEND,
};

void	redirect_out(char *filename, enum e_mode mode)
{
	int	fd;
	int	option;

	option = O_WRONLY | O_CREAT;
	if (mode == OVERWRITE)
		option |= O_TRUNC;
	else if (mode == APPEND)
		option |= O_APPEND;
	fd = open(filename, option, 0644);
	catch_error(fd, filename);
	catch_error(dup2(fd, STDOUT_FILENO), "dup2");
	catch_error(close(fd), "close");
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
		catch_error(write(STDOUT_FILENO, data, ft_strlen(data) + 1), "write");
		exit(0);
	}
	connect_pipe(pipefd, STDIN_FILENO);
}

/**
 * <redirection list>	::= <redirection> <redirection list>
 * <redirection>		::= '<' <filename> <token list>
 *						  | '>' <filename> <token list>
 *						  | '<<' <filename> <token list>
 *						  | '>>' <filename> <token list>
 */
void	execute_redirection(t_astree *tree)
{
	while (tree && tree->type & NODE_REDIRECT_LIST)
	{
		if (tree->left->type & NODE_REDIRECT_IN)
			redirect_in(tree->left->data);
		else if (tree->left->type & NODE_REDIRECT_OUT)
			redirect_out(tree->left->data, OVERWRITE);
		else if (tree->left->type & NODE_REDIRECT_OUT2)
			redirect_out(tree->left->data, APPEND);
		else if (tree->left->type & NODE_REDIRECT_IN2)
			redirect_heredoc(tree->left->data);
		tree = tree->right;
	}
}
