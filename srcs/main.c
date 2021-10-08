#include "shell.h"

t_shell	g_shell = {};

void	clear_line(char **input, t_lexer **lex, t_astree **tree)
{
	lexer_free(lex);
	*tree = astree_delete_node(*tree);
	free_set((void **)input, NULL);
}

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
		{
			expand_astree(tree);
			g_shell.exit_status = minishell_execute(tree);
		}
		clear_line(&input, &lex, &tree);
	}
}
