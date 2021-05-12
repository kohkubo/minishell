#include "../includes/shell.h"
#include <stdio.h>

int	main(void)
{
	int		status;
	char	*input;

	status = 1;
	while (status)
	{
		if (get_next_line(0, &input) <= 0)
			break ;
		parse(input);
		free(input);
	}
	return (0);
}
