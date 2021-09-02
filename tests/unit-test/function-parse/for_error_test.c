#include <stdio.h>
#include "shell.h"
#include "lex.h"

int main(int argc, char *argv[])
{
	t_lexer		*lex;
	t_astree	*tree;

	printf("%s\n", argv[1]);
	// minishell_lexer(argv[1], &lex);
	// parse_v2(lex, &tree);
}
