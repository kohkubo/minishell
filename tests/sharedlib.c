#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

__attribute__((destructor))
void	destructor(void)
{
	int	status;

	status = system("leaks minishell &> leaksout");
	if (status)
	{
		write(2, "leak!!!\n", 8);
		system("cat leaksout >/dev/stderr");
		exit(1);
	}
}
