#include "shell.h"

t_shell	g_shell = {};

int	main(void)
{
	char		*input;
	t_lexer		*lex;
	t_astree	*tree;

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
		lex = NULL;
		minishell_lexer(input, &lex);
		tree = NULL;
		if (parse_v2(lex, &tree))
			g_shell.exit_status = minishell_execute(tree);
		lexer_free(&lex);
		tree = astree_delete_node(tree);
		free_set((void **)&input, NULL);
	}
	return (0);
}
