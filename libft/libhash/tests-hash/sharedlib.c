#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

void	destructor(void)__attribute__((destructor));

void	destructor(void)
{
	int		status;
	char	buf[50];

	snprintf(buf, 50, "leaks -q %d &> leaksout", getpid());
	status = system(buf);
	if (status)
	{
		write(2, "leak!!!\n", 8);
		system("cat leaksout >/dev/stderr");
		exit(1);
	}
}
