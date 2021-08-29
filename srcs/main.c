#include "shell.h"

t_shell	g_shell;

int	main(void)
{
	char	*input;

	minishell_init();
	input = NULL;
	while (1)
	{
		input = readline(PROMPT);
		if (input == NULL || ft_strlen(input) == 0)
		{
			free_set((void **)&input, NULL);
			break ;
		}
		add_history(input);
		parse(input);
		free_set((void **)&input, NULL);
	}
	return (0);
}
