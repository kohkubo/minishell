#include "../includes/shell.h"
#include <stdio.h>

int	main(void)
{
	int		status;
	char	*input;

	status = 1;
	while (status)
	{
		ft_putstr_fd("> ", 1);
		if (get_next_line(0, &input) <= 0)
		ft_putendl_fd(input, 1);
		free(input);
	}
	return (0);
}
