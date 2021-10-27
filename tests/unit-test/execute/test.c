#include "shell.h"

t_shell	g_shell = {};

int main(int argc, char *argv[])
{
	t_lexer		*lex;
	t_astree	*tree;
	int			status;
	char		*input;

	minishell_init(&input, &lex, &tree);
	minishell_lexer(argv[1], &lex);
	parse(lex, &tree);
	expand_astree(tree);
	status = minishell_execute(tree);
	lexer_free(&lex);
	tree = astree_delete_node(tree);
	return (status);
}
