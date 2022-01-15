#include "shell.h"

t_shell	g_shell = {};

int	main(void)
{
	char		*input;
	t_lexer		*lex;
	t_astree	*tree;

	minishell_init(&input, &lex, &tree);
	while (1)
	{
		free_set(&input, NULL), input = readline(PROMPT);
		if (input == NULL)
			exit(g_shell.exit_status);
		if (ft_strlen(input) == 0)
			continue ;
		add_history(input);
		if (minishell_lexer(input, &lex) != STATE_GENERAL)
		{
			lexer_free(&lex);
			continue ;
		}
		if (parse(lex, &tree))
		{
			expand_astree(tree);
			g_shell.exit_status = minishell_execute(tree);
		}
		lexer_free(&lex), tree = astree_delete_node(tree);
	}
}
