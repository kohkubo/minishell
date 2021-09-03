#include "shell.h"

t_shell	g_shell = {};

int main(int argc, char *argv[])
{
	t_lexer		*lex;
	t_astree	*tree;

	minishell_init();
	minishell_lexer(argv[1], &lex);
	parse_v2(lex, &tree);
	minishell_execute(tree);
	lexer_free(&lex);
	tree = astree_delete_node(tree);
}
