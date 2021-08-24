#include <string.h>
#include "shell.h"
#include "lex.h"
#include "astree.h"
#include "libft.h"
#include "logging.h"

void print_token(void *tok)
{
	t_tok *token;

	token = (t_tok *)tok;
	printf("[%3d] "YELLOW"%s"END"\n", token->type, token->data);
}

void	print_tree(t_astree *node, int sp_num)
{
	char	*str;

	if (sp_num != 0)
		printf(" ");
	if (node == NULL)
	{
		printf(BLACK"(null)\n"END);
		return ;
	}
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

bool	compare(t_astree *ex, t_astree *ac)
{
	if (ex == NULL && ac == NULL)
		return (true);
	if ((ex == NULL && ac != NULL)
		|| (ex != NULL && ac == NULL))
	{
		fprintf(stderr, RED"One is NULL.\n"END);
		fprintf(stderr, "expect: %p, actualy: %p\n", ex, ac);
		return (false);
	}
	if (ex->type != ac->type)
	{
		fprintf(stderr, RED"type is different.\n"END);
		fprintf(stderr, "expect: %d, actualy: %d\n", ex->type, ac->type);
		return (false);
	}
	if (!(ex->data == NULL && ac->data == NULL))
	{
		if (strcmp(ex->data, ac->data))
		{
			fprintf(stderr, RED"data is different.\n"END);
			fprintf(stderr, "expect: %s, actualy: %s\n", ex->data, ac->data);
			return (false);
		}
	}
	if (!compare(ex->left, ac->left))
		return (false);
	return (compare(ex->right, ac->right));
}

void	test(bool verbose, char *input, t_astree *expect_tree)
{
	t_lexer		*lex;
	t_astree	*res_tree;
	bool		res_flg;
	bool		is_ok;

	printf("%s", input);
	minishell_lexer(input, &lex);
	if (verbose)
		ft_lstiter(lex->listtok, print_token);
	res_tree = NULL;
	res_flg = parse_v2(lex, &res_tree);
	if (verbose)
	{
		printf("----- expect -----\n");
		print_tree(expect_tree, 0);
		printf("----- actualy -----\n");
		print_tree(res_tree, 0);
	}
	is_ok = compare(expect_tree, res_tree);
	lexer_free(&lex);
	res_tree = astree_delete_node(res_tree);
	expect_tree = astree_delete_node(expect_tree);
	if (res_flg && is_ok)
		printf(GREEN" ✓\n"END);
	else
	{
		printf(RED" ×\n"END);
		if (!res_flg)
			fprintf(stderr, RED"return val is different.\n"END);
	}
}

int main(void) {
	bool	varbose;

	varbose = false;
	// バッファリング無効
	setvbuf(stdout, 0, _IONBF, 0);
	setvbuf(stderr, 0, _IONBF, 0);
	/*
	 * <token list> ::= (EMPTY)
	 */
	printf(BOLD"--- (EMPTY) ---\n"END);
	printf("(no-length string)");
	test(varbose, "", NULL);
	printf("(white space only)");
	test(varbose, "    ", NULL);
	/*
	 * <token list>		::= <token> <token list>
	 * <simple command>	::= <pathname> <token list>
	 * <command>		::= <simple command>
	 */
	// <pathname> (EMPTY)
	test(varbose, "pwd",
		astree_create_node( // RIGHT
			NODE_CMDPATH | NODE_DATA,
			strdup("pwd"),
			NULL,
			NULL));
	// <pathname> <token>
	test(varbose, "echo a",
		astree_create_node(
			NODE_CMDPATH | NODE_DATA,
			strdup("echo"),
			NULL, // LEFT
			astree_create_node( // RIGHT
				NODE_ARGUMENT | NODE_DATA,
				strdup("a"),
				NULL,
				NULL)));
	// <pathname> <token list>
	test(varbose, "token1 token2 token3 token4",
		astree_create_node(
			NODE_CMDPATH | NODE_DATA,
			strdup("token1"),
			NULL, // LEFT
			astree_create_node( // RIGHT
				NODE_ARGUMENT | NODE_DATA,
				strdup("token2"),
				NULL, // LEFT
				astree_create_node( // RIGHT
					NODE_ARGUMENT | NODE_DATA,
					strdup("token3"),
					NULL, // LEFT
					astree_create_node( // RIGHT
						NODE_ARGUMENT | NODE_DATA,
						strdup("token4"),
						NULL,
						NULL)))));
	/*
	 * <command>			::= <simple command> <redirection list>
	 * <redirection list>	::= <redirection> <redirection list>
	 * <redirection>		::= '<' <filename> <token list>
	 */
	// <simple command> <redirection>
	test(varbose, "cat < in1",
		astree_create_node(
			NODE_REDIRECTION,
			NULL,
			astree_create_node( // LEFT
				NODE_CMDPATH | NODE_DATA,
				strdup("cat"),
				NULL, // LEFT
				NULL), // RIGHT
			astree_create_node( // RIGHT
				NODE_REDIRECT_LIST,
				NULL,
				astree_create_node( // LEFT
					NODE_REDIRECT_IN | NODE_DATA,
					strdup("in1"),
					NULL, // LEFT
					NULL), // RIGHT
				NULL))); // RIGHT
	test(varbose, "cat > out1",
		astree_create_node(
			NODE_REDIRECTION,
			NULL,
			astree_create_node( // LEFT
				NODE_CMDPATH | NODE_DATA,
				strdup("cat"),
				NULL, // LEFT
				NULL), // RIGHT
			astree_create_node( // RIGHT
				NODE_REDIRECT_LIST,
				NULL,
				astree_create_node( // LEFT
					NODE_REDIRECT_OUT | NODE_DATA,
					strdup("out1"),
					NULL, // LEFT
					NULL), // RIGHT
				NULL))); // RIGHT
	test(varbose, "cat >> out1",
		astree_create_node(
			NODE_REDIRECTION,
			NULL,
			astree_create_node( // LEFT
				NODE_CMDPATH | NODE_DATA,
				strdup("cat"),
				NULL, // LEFT
				NULL), // RIGHT
			astree_create_node( // RIGHT
				NODE_REDIRECT_LIST,
				NULL,
				astree_create_node( // LEFT
					NODE_REDIRECT_OUT2 | NODE_DATA,
					strdup("out1"),
					NULL, // LEFT
					NULL), // RIGHT
				NULL))); // RIGHT
	// // <simple command> <redirection list>
	// TODO
	// test(true, "cat < in1 < in2",

	// 	);
	// test("cat > out1 > out2");
	// test("cat >> out1 >> out2");
	// // <simple command> <redirection> <token>
	// test("cat < in1 arg1");
	// test("cat arg1 < in1 arg2");
	// // <simple command> <redirection> <token list>
	// test("cat < in1 arg1 arg2");
	// test("cat arg1 < in1 arg2 arg3");
	// // <simple command> <redirection list> <token>
	// test("cat < in1 < in2 arg1");
	// test("cat arg1 < in1 < in2 arg2");
	// test("cat < in1 arg1 < in2");
	// test("cat arg1 < in1 arg2 < in2");
	// // <simple command> <redirection list> <token list>
	// test("cat < in1 arg1 arg2 < in2");
	// test("cat arg1 < in1 arg2 arg3 < in2");
	// error
	// error_test(varbose, "cat < <", "syntax error near unexpected token `<'");
	// 	test("cat < out test;;"); // ';;'
	// 	test("cat < ;"); // ';'
	// /*
	//  * <redirection> ::= '>' <filename> <token list>
	//  */
	// test("echo a > testfile");
	// test("echo a > testfile b");
	// test("echo a > test1 b b b b b  > test2");
	// 	// error
	// 	test("echo >"); // 'newline';
	// /*
	//  * <redirection> ::= '<<' <token> <token list>
	//  */
	// // test("cat << test");
	// /*
	//  * <redirection> ::= '>>' <filename> <token list>
	//  */
	// test("echo a >> testfile");
	// test("echo a >> testfile b");
	// test("echo a >> test1 b b b b b  > test2");
	// 	// error
	// 	test("echo >>"); // 'newline';

	// /*
	//  * <command line> ::= <job>
	//  * <job> ::= <command>
	//  * <job> ::= <command> '|' <job>
	//  */
	// test("echo a | tr a A");
	// test("echo a|");
	// /*
	//  * <command line> ::= <job> ;
	//  */
	// test("echo a;");
	// test("a;");
	// test("a b c d e f g;");
	// 	//error
	// 	test("echo a;;"); // ';;'
	// 	test("echo a;; ;"); // ';;'
	// /*
	//  * <command line> ::= <job> ; <command line>
	//  */
	// test("echo a; echo b");
	// test("echo b; echo ; HOGE c c c c");
	// test("echo c; HOGE d d d d;");
	// 	//error
	// 	test("echo a; ;"); // ';'
	// 	test("echo b; ; HOGE c c c c"); // ';'
	// /*
	//  * <command line> ::= <job> & // not make
	//  * <command line> ::= <job> & <command line> // not make
	//  */
}
