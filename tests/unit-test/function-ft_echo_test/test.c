#include <stdio.h>
#include <libc.h>
#include "./../../../includes/shell.h"

int	main(void)
{
	int backup = dup(STDOUT_FILENO);
	int fd = open("./output", O_RDWR);
	int i = dup2(fd, STDOUT_FILENO);

	if (ft_echo(1, "aiueo") != 0)
		exit(1);
	fflush(stdout);
	if (ft_echo(2, "aiueo", "test") != 0)
		exit(1);
	fflush(stdout);
	if (ft_echo(3, "-n", "aiueo", "test") != 0)
		exit(1);
	fflush(stdout);
	if (ft_echo(1, "-n") != 0)
		exit(1);
	fflush(stdout);
	if (ft_echo(1, "") != 0)
		exit(1);
	fflush(stdout);
	if (ft_echo(2, "-n", "") != 0)
		exit(1);
	fflush(stdout);
	if (ft_echo(0, NULL) != 0)
		exit(1);
	fflush(stdout);

	// エラーケース
	if (ft_echo(1, NULL) != 1)
		exit(1);
	fflush(stdout);
	if (ft_echo(2, "test", NULL) != 1)
		exit(1);
	fflush(stdout);
	if (ft_echo(2, NULL, NULL) != 1)
		exit(1);
	fflush(stdout);
	if (ft_echo(0) != 0)
		exit(1);
	fflush(stdout);
	dup2(backup, STDOUT_FILENO);
	close(backup);

	return (0);
}
