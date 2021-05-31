#include "../includes/shell.h"

int	main(void)
{
	char	*input;

	input = NULL;
	while (1)
	{
		if (get_next_line(0, &input) <= 0)
			break ;
		parse(input);
		free_set((void **)&input, NULL);
	}
	free_set((void **)&input, NULL);
	return (0);
}
