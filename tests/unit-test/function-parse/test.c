#include "shell.h"
#include "lex.h"
#include "astree.h"
#include "libft.h"
#include "logging.h"

// print token
void print_token(void *tok)
{
	t_tok *token;

	token = (t_tok *)tok;
	printf("[%3d] "YELLOW"%s"END"\n", token->type, token->data);
}

void	print_tree(t_astree *node, int sp_num)
{
	if (sp_num != 0)
		printf(" ");
	if (node == NULL)
	{
		printf(BLACK"(null)\n"END);
		return ;
	}
	char *str;
	if (node->type & NODE_PIPE)
		str = "PIPE";
	else if (node->type & NODE_BCKGRND)
		str = "BCKGRND";
	else if (node->type & NODE_SEQ)
		str = "SEQ";
	else if (node->type & NODE_REDIRECT_IN)
		str = "REDIRECT_IN";
	else if (node->type & NODE_REDIRECT_OUT)
		str = "REDIRECT_OUT";
	else if (node->type & NODE_REDIRECT_IN2)
		str = "REDIRECT_IN2";
	else if (node->type & NODE_REDIRECT_OUT2)
		str = "REDIRECT_OUT2";
	else if (node->type & NODE_CMDPATH)
		str = "CMDPATH";
	else if (node->type & NODE_ARGUMENT)
		str = "ARGUMENT";
	else if (node->type & NODE_REDIRECT_LIST)
		str = "REDIRECT_LIST";
	else if (node->type & NODE_REDIRECTION)
		str = "REDIRECTION";
	else
		str = BOLD RED"NOT FOUND"END;


	if (node->type & NODE_DATA)
		printf(YELLOW"%s"END"("BLUE"%s"END")\n", node->data, str);
	else
		printf(BOLD BLUE"%s\n"END, str);

	printf("%*s", sp_num, "");
	printf("├");
	print_tree(node->left, sp_num + 2);
	printf("%*s", sp_num, "");
	printf("└");
	print_tree(node->right, sp_num + 2);
}

void test(char *input) {
	t_lexer *lex;
	t_astree *tree;
	t_astree *expect;

	printf(BOLD"%s\n"END, input);
	lex = minishell_lexer(input);
	ft_lstiter(lex->listtok, print_token);
	tree = NULL;
	parse_v2(lex, &tree);
	print_tree(tree, 0);

	// expect = astree_create_node(NODE_SEQ, NULL,
	// 			astree_create_node(NODE_CMDPATH | NODE_DATA, "echo",
	// 				NULL,
	// 				astree_create_node()),
	// 			astree_create_node());

	lexer_free(&lex);
	tree = astree_delete_node(tree);
}

int main(void) {

	/*
	 * <token list> ::= (EMPTY)
	 */
	printf("(no-length string)\n");
	test("");
	printf("(white space only)\n");
	test("    ");
	/*
	 * <token list>		::= <token> <token list>
	 * <simple command>	::= <pathname> <token list>
	 * <command>		::= <simple command>
	 */
	test("token");
	test("token token token token");
	test("echo a");
	test("echo b b b b b b b b b b");
	/*
	 * <command>			::= <simple command> <redirection list>
	 * <redirection list>	::= <redirection> <redirection list>
	 * <redirection>		::= '<' <filename> <token list>
	 */
	test("cat < test");
	test("cat < test1 < test2 < test3");
	test("cat test1 < out test2");
	test("cat test1 < a b b b b b b < c");
		// error
		test("cat < out test;;"); // ';;'
		test("cat < ;"); // ';'
	/*
	 * <redirection> ::= '>' <filename> <token list>
	 */
	test("echo a > testfile");
	test("echo a > testfile b");
	test("echo a > test1 b b b b b  > test2");
		// error
		test("echo >"); // 'newline';
	/*
	 * <redirection> ::= '<<' <token>
	 */
	// test("cat << test");
	/*
	 * <redirection> ::= '>>' <filename> <token list>
	 */
	test("echo a >> testfile");
	test("echo a >> testfile b");
	test("echo a >> test1 b b b b b  > test2");
		// error
		test("echo >>"); // 'newline';

	/*
	 * <command line> ::= <job>
	 * <job> ::= <command>
	 * <job> ::= <command> '|' <job>
	 */
	test("echo a | tr a A");
	/*
	 * <command line> ::= <job> ;
	 */
	test("echo a;");
	test("a;");
	test("a b c d e f g;");
		//error
		test("echo a;;"); // ';;'
		test("echo a;; ;"); // ';;'
	/*
	 * <command line> ::= <job> ; <command line>
	 */
	test("echo a; echo b");
	test("echo b; echo ; HOGE c c c c");
	test("echo c; HOGE d d d d;");
		//error
		test("echo a; ;"); // ';'
		test("echo b; ; HOGE c c c c"); // ';'
	/*
	 * <command line> ::= <job> & // not make
	 * <command line> ::= <job> & <command line> // not make
	 */



}
