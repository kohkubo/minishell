#include "shell.h"

#include <string.h>
#include <stdbool.h>
#include <fcntl.h>
#include "exec.h"
#include "logging.h"

t_shell g_shell = {};

int	diff()
{
	int diff;

	diff = system("diff expect out > /dev/null");
	if (diff == 0)
		ft_putendl_fd(GREEN" ✓"END, 1);
	else
	{
		ft_putendl_fd(RED" ×"END, 1);
		printf("%37s | %s\n", "expect", "actuary");
		for (size_t i = 0; i < 38; i++)
			printf("-");
		printf("+");
		for (size_t i = 0; i < 38; i++)
			printf("-");
		printf("\n");
		system("diff -y -W 79 expect out");
		ft_putstr_fd(END, 1);
	}
	return (diff);
}

enum e_status_mean
{
	EXPECT,
	ACTUAL,
	DIFF,
	STATUS_LEN
};

bool	cmp_status(int status[STATUS_LEN])
{
	if (status[EXPECT] == status[ACTUAL])
	{
		ft_putstr_fd(GREEN" ✓"END, 1);
		return (true);
	}
	else
	{
		ft_putstr_fd(RED" ×(EX: ", 1);
		ft_putnbr_fd(status[EXPECT], 1);
		ft_putstr_fd(", AC: ", 1);
		ft_putnbr_fd(status[ACTUAL], 1);
		ft_putstr_fd(")"END, 1);
		return (false);
	}
}

enum e_mean_fd
{
	OUT,
	STDOUT_BACKUP,
	STDERR_BACKUP,
	FD_LEN
};

int	make_actual(t_astree *tree)
{
	int		fd[FD_LEN];
	int		status;

	// set redirecttion
	fd[OUT] = open("out", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	fd[STDOUT_BACKUP] = dup(STDOUT_FILENO);
	fd[STDERR_BACKUP] = dup(STDERR_FILENO);
	dup2(fd[OUT], STDOUT_FILENO);
	dup2(fd[OUT], STDERR_FILENO);
	close(fd[OUT]);
	// do
	status = minishell_execute(tree);
	// unset redirection
	dup2(fd[STDOUT_BACKUP], STDOUT_FILENO);
	dup2(fd[STDERR_BACKUP], STDERR_FILENO);
	return (status);
}

int	make_expect(char *cmd)
{
	char	buf[1024];
	int		status;

	snprintf(buf, 1024, "(%s) &> expect", cmd);
	status = system(buf);
	return (get_status(status));
}

bool	test(char* cmd, t_astree	**tree)
{
	int		status[FD_LEN];
	bool	isSuccess;

	status[EXPECT] = make_expect(cmd);
	status[ACTUAL] = make_actual(*tree);
	ft_putstr_fd(cmd, 1);
	isSuccess = cmp_status(status);
	status[DIFF] = diff();
	isSuccess &= !status[DIFF];
	*tree = astree_delete_node(*tree);
	return (isSuccess);
}

int main(int argc, char *argv[])
{
	t_astree	*input;
	bool		isSuccess;

	char *a; t_lexer* b; t_astree *c;
	minishell_init(&a, &b, &c);
	isSuccess = true;

	/*
	** single success
	*/
	input = astree_create_node(NODE_CMDPATH | NODE_DATA, strdup("whoami"),
				NULL,
				NULL);
	isSuccess &= test("whoami", &input);

	/*
	** single failure
	*/
	input = astree_create_node(NODE_CMDPATH | NODE_DATA, strdup("gcc"),
				NULL,
				NULL);
	isSuccess &= test("gcc", &input);

	/*
	** double success
	*/
	input = astree_create_node(NODE_AND, NULL,
				astree_create_node(NODE_CMDPATH | NODE_DATA, strdup("whoami"),
					NULL,
					NULL),
				astree_create_node(NODE_CMDPATH | NODE_DATA, strdup("whoami"),
					NULL,
					NULL));
	isSuccess &= test("whoami && whoami", &input);

	input = astree_create_node(NODE_OR, NULL,
				astree_create_node(NODE_CMDPATH | NODE_DATA, strdup("whoami"),
					NULL,
					NULL),
				astree_create_node(NODE_CMDPATH | NODE_DATA, strdup("whoami"),
					NULL,
					NULL));
	isSuccess &= test("whoami || whoami", &input);

	/*
	** double failure
	*/
	input = astree_create_node(NODE_AND, NULL,
				astree_create_node(NODE_CMDPATH | NODE_DATA, strdup("gcc"),
					NULL,
					NULL),
				astree_create_node(NODE_CMDPATH | NODE_DATA, strdup("whoami"),
					NULL,
					NULL));
	isSuccess &= test("gcc && whoami", &input);

	input = astree_create_node(NODE_OR, NULL,
				astree_create_node(NODE_CMDPATH | NODE_DATA, strdup("gcc"),
					NULL,
					NULL),
				astree_create_node(NODE_CMDPATH | NODE_DATA, strdup("whoami"),
					NULL,
					NULL));
	isSuccess &= test("gcc || whoami", &input);

	/*
	** triple success success
	*/
	input = astree_create_node(NODE_AND, NULL,
				astree_create_node(NODE_CMDPATH | NODE_DATA, strdup("whoami"),
					NULL,
					NULL),
				astree_create_node(NODE_AND, NULL,
					astree_create_node(NODE_CMDPATH | NODE_DATA, strdup("whoami"),
						NULL,
						NULL),
					astree_create_node(NODE_CMDPATH | NODE_DATA, strdup("whoami"),
						NULL,
						NULL)));
	isSuccess &= test("whoami && whoami && whoami", &input);
	
	input = astree_create_node(NODE_AND, NULL,
				astree_create_node(NODE_CMDPATH | NODE_DATA, strdup("whoami"),
					NULL,
					NULL),
				astree_create_node(NODE_OR, NULL,
					astree_create_node(NODE_CMDPATH | NODE_DATA, strdup("whoami"),
						NULL,
						NULL),
					astree_create_node(NODE_CMDPATH | NODE_DATA, strdup("whoami"),
						NULL,
						NULL)));
	isSuccess &= test("whoami && whoami || whoami", &input);

	/*
	** triple success failure
	*/
	input = astree_create_node(NODE_AND, NULL,
				astree_create_node(NODE_CMDPATH | NODE_DATA, strdup("whoami"),
					NULL,
					NULL),
				astree_create_node(NODE_AND, NULL,
					astree_create_node(NODE_CMDPATH | NODE_DATA, strdup("gcc"),
						NULL,
						NULL),
					astree_create_node(NODE_CMDPATH | NODE_DATA, strdup("whoami"),
						NULL,
						NULL)));
	isSuccess &= test("whoami && gcc && whoami", &input);
	
	input = astree_create_node(NODE_AND, NULL,
				astree_create_node(NODE_CMDPATH | NODE_DATA, strdup("whoami"),
					NULL,
					NULL),
				astree_create_node(NODE_OR, NULL,
					astree_create_node(NODE_CMDPATH | NODE_DATA, strdup("gcc"),
						NULL,
						NULL),
					astree_create_node(NODE_CMDPATH | NODE_DATA, strdup("whoami"),
						NULL,
						NULL)));
	isSuccess &= test("whoami && gcc || whoami", &input);

	return (!isSuccess);
}
