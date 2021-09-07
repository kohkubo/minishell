#include <stdio.h>
#include "shell.h"
#include "lex.h"

int main(int argc, char *argv[])
{
	t_lexer		*lex;
	t_astree	*tree;
	bool		isSuccess;

	minishell_lexer(argv[1], &lex);
	isSuccess = parse_v2(lex, &tree);
	lexer_free(&lex);
	tree = astree_delete_node(tree);
	return (!isSuccess);
}
