#include <string.h>
#include "shell.h"
#include "lex.h"
#include "astree.h"
#include "libft.h"
#include "libex.h"
#include "logging.h"

t_shell	g_shell = {};

void print_token(void *tok)
{
	t_tok *token;

	token = (t_tok *)tok;
	printf("[%3d] "YELLOW"%s"END"\n", token->type, token->data);
}

char	*get_typestr(t_node_type type)
{
	char	*str;

	str = ft_xstrdup("");
	if (type & NODE_PIPE)
		free_set((void **)&str, ft_xstrjoin(str, " | NODE_PIPE"));
	if (type & NODE_BCKGRND)
		free_set((void **)&str, ft_xstrjoin(str, " | NODE_BCKGRND"));
	if (type & NODE_SEQ)
		free_set((void **)&str, ft_xstrjoin(str, " | NODE_SEQ"));
	if (type & NODE_REDIRECT_IN)
		free_set((void **)&str, ft_xstrjoin(str, " | NODE_REDIRECT_IN"));
	if (type & NODE_REDIRECT_OUT)
		free_set((void **)&str, ft_xstrjoin(str, " | NODE_REDIRECT_OUT"));
	if (type & NODE_REDIRECT_IN2)
		free_set((void **)&str, ft_xstrjoin(str, " | NODE_REDIRECT_IN2"));
	if (type & NODE_REDIRECT_OUT2)
		free_set((void **)&str, ft_xstrjoin(str, " | NODE_REDIRECT_OUT2"));
	if (type & NODE_CMDPATH)
		free_set((void **)&str, ft_xstrjoin(str, " | NODE_CMDPATH"));
	if (type & NODE_ARGUMENT)
		free_set((void **)&str, ft_xstrjoin(str, " | NODE_ARGUMENT"));
	if (type & NODE_REDIRECT_LIST)
		free_set((void **)&str, ft_xstrjoin(str, " | NODE_REDIRECT_LIST"));
	if (type & NODE_REDIRECTION)
		free_set((void **)&str, ft_xstrjoin(str, " | NODE_REDIRECTION"));
	if (type & NODE_DATA)
		free_set((void **)&str, ft_xstrjoin(str, " | NODE_DATA"));
	free_set((void **)&str, ft_strtrim(str, "| "));
	return (str);
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
		fprintf(stderr, RED"\nOne is NULL.\n"END);
		fprintf(stderr, "expect: %p, actualy: %p\n", ex, ac);
		return (false);
	}
	if (ex->type != ac->type)
	{
		fprintf(stderr, RED"\ntype is different.\n"END);
		char *ex_type = get_typestr(ex->type);
		char *ac_type = get_typestr(ac->type);
		fprintf(stderr, "expect: %s, actualy: %s\n", ex_type, ac_type);
		free(ex_type), free(ac_type);
		return (false);
	}
	if (!(ex->data == NULL && ac->data == NULL))
	{
		if (strcmp(ex->data, ac->data))
		{
			fprintf(stderr, RED"\ndata is different.\n"END);
			fprintf(stderr, "expect: %s, actualy: %s\n", ex->data, ac->data);
			return (false);
		}
	}
	if (!compare(ex->left, ac->left))
		return (false);
	return (compare(ex->right, ac->right));
}

bool	test(bool varbose, char *input, t_astree *expect_tree)
{
	t_lexer		*lex;
	t_astree	*res_tree;
	bool		res_flg;
	bool		is_ok;

	if (varbose)
		printf(BOLD"%s\n"END, input);
	else
		printf("%s", input);
	minishell_lexer(input, &lex);
	if (varbose)
		ft_lstiter(lex->listtok, print_token);
	res_tree = NULL;
	res_flg = parse_v2(lex, &res_tree);
	if (varbose)
	{
		printf("----- expect -----\n");
		print_tree(expect_tree, 0);
		printf("----- actualy -----\n");
		print_tree(res_tree, 0);
	}
	is_ok = compare(expect_tree, res_tree);
	is_ok = is_ok && g_shell.exit_status == 0;
	lexer_free(&lex);
	res_tree = astree_delete_node(res_tree);
	expect_tree = astree_delete_node(expect_tree);
	if (res_flg && is_ok)
	{
		printf(GREEN" ✓\n"END);
		return (true);
	}
	else
	{
		printf(RED" ×\n"END);
		if (!res_flg)
			fprintf(stderr, RED"return val is different.\n"END);
		if (g_shell.exit_status != 0)
			fprintf(stderr, RED"exit status is different.(%d)\n"END, g_shell.exit_status);
		return (false);
	}
}

int main(void) {
	bool	varbose;
	bool	result;

	varbose = false;
	result = true;
	// バッファリング無効
	setvbuf(stdout, 0, _IONBF, 0);
	setvbuf(stderr, 0, _IONBF, 0);
	/*
	 * <token list> ::= (EMPTY)
	 */
	printf("(no-length string)");
	result &= test(varbose, "", NULL);
	printf("(white space only)");
	result &= test(varbose, "    ", NULL);
	/*
	 * <token list>		::= <token> <token list>
	 * <simple command>	::= <pathname> <token list>
	 * <command>		::= <simple command>
	 */
	// <pathname> (EMPTY)
	result &= test(varbose, "pwd",
		astree_create_node(NODE_CMDPATH | NODE_DATA, strdup("pwd"),
			NULL, // LEFT
			NULL)); // RIGHT
	// <pathname> <token>
	result &= test(varbose, "echo a",
		astree_create_node(NODE_CMDPATH | NODE_DATA, strdup("echo"),
			NULL,
			astree_create_node(NODE_ARGUMENT | NODE_DATA, strdup("a"),
				NULL,
				NULL)));
	// <pathname> <token list>
	result &= test(varbose, "token1 token2 token3 token4",
		astree_create_node(NODE_CMDPATH | NODE_DATA, strdup("token1"),
			NULL,
			astree_create_node(NODE_ARGUMENT | NODE_DATA, strdup("token2"),
				NULL,
				astree_create_node(NODE_ARGUMENT | NODE_DATA, strdup("token3"),
					NULL,
					astree_create_node(NODE_ARGUMENT | NODE_DATA,
						strdup("token4"),
						NULL,
						NULL)))));
	/*
	 * <command>			::= <simple command> <redirection list>
	 * <redirection list>	::= <redirection> <redirection list>
	 * <redirection>		::= '<' <filename> <token list>
	 */
	// <redirection list>
	result &= test(varbose, "< in1",
		astree_create_node(NODE_REDIRECT_LIST, NULL,
			astree_create_node(NODE_REDIRECT_IN | NODE_DATA, strdup("in1"),
				NULL,
				NULL),
			NULL));
	result &= test(varbose, "< in1 > out1",
		astree_create_node(NODE_REDIRECT_LIST, NULL,
			astree_create_node(NODE_REDIRECT_IN | NODE_DATA, strdup("in1"),
				NULL,
				NULL),
			astree_create_node(NODE_REDIRECT_LIST, NULL,
				astree_create_node(NODE_REDIRECT_OUT | NODE_DATA, strdup("out1"),
					NULL,
					NULL),
				NULL)));

	// <simple command> <redirection>
	result &= test(varbose, "cat < in1",
		astree_create_node(NODE_REDIRECTION, NULL,
			astree_create_node(NODE_CMDPATH | NODE_DATA,
				strdup("cat"),
				NULL,
				NULL),
			astree_create_node(NODE_REDIRECT_LIST, NULL,
				astree_create_node(NODE_REDIRECT_IN | NODE_DATA, strdup("in1"),
					NULL,
					NULL),
				NULL)));
	result &= test(varbose, "cat > out1",
		astree_create_node(NODE_REDIRECTION, NULL,
			astree_create_node(NODE_CMDPATH | NODE_DATA, strdup("cat"),
				NULL,
				NULL),
			astree_create_node(NODE_REDIRECT_LIST, NULL,
				astree_create_node(NODE_REDIRECT_OUT | NODE_DATA, strdup("out1"),
					NULL,
					NULL),
				NULL)));
	result &= test(varbose, "cat >> out1",
		astree_create_node(NODE_REDIRECTION, NULL,
			astree_create_node(NODE_CMDPATH | NODE_DATA,
				strdup("cat"),
				NULL,
				NULL),
			astree_create_node(NODE_REDIRECT_LIST, NULL,
				astree_create_node(NODE_REDIRECT_OUT2 | NODE_DATA, strdup("out1"),
					NULL,
					NULL),
				NULL)));
	// // <simple command> <redirection list>
	result &= test(varbose, "cat < in1 < in2",
		astree_create_node(NODE_REDIRECTION, NULL,
			astree_create_node(NODE_CMDPATH | NODE_DATA, strdup("cat"),
				NULL,
				NULL),
			astree_create_node(NODE_REDIRECT_LIST, NULL,
				astree_create_node(NODE_REDIRECT_IN | NODE_DATA, strdup("in1"),
					NULL,
					NULL),
				astree_create_node(NODE_REDIRECT_LIST, NULL,
						astree_create_node(NODE_REDIRECT_IN | NODE_DATA, strdup("in2"),
							NULL,
							NULL),
						NULL))));
	result &= test(varbose, "cat > out1 > out2",
		astree_create_node(NODE_REDIRECTION, NULL,
			astree_create_node(NODE_CMDPATH | NODE_DATA, strdup("cat"),
				NULL,
				NULL),
			astree_create_node(NODE_REDIRECT_LIST, NULL,
				astree_create_node(NODE_REDIRECT_OUT | NODE_DATA, strdup("out1"),
					NULL,
					NULL),
				astree_create_node(NODE_REDIRECT_LIST, NULL,
						astree_create_node(NODE_REDIRECT_OUT | NODE_DATA, strdup("out2"),
							NULL,
							NULL),
						NULL))));
	result &= test(varbose, "cat >> out1 >> out2",
		astree_create_node(NODE_REDIRECTION, NULL,
			astree_create_node(NODE_CMDPATH | NODE_DATA, strdup("cat"),
				NULL,
				NULL),
			astree_create_node(NODE_REDIRECT_LIST, NULL,
				astree_create_node(NODE_REDIRECT_OUT2 | NODE_DATA, strdup("out1"),
					NULL,
					NULL),
				astree_create_node(NODE_REDIRECT_LIST, NULL,
						astree_create_node(NODE_REDIRECT_OUT2 | NODE_DATA, strdup("out2"),
							NULL,
							NULL),
						NULL))));
	// // <simple command> <redirection> <token>
	result &= test(varbose, "cat < in1 arg1",
		astree_create_node(NODE_REDIRECTION, NULL,
			astree_create_node(NODE_CMDPATH | NODE_DATA, strdup("cat"),
				NULL,
				astree_create_node(NODE_ARGUMENT | NODE_DATA, strdup("arg1"),
					NULL,
					NULL)),
			astree_create_node(NODE_REDIRECT_LIST, NULL,
				astree_create_node(NODE_REDIRECT_IN | NODE_DATA, strdup("in1"),
					NULL,
					NULL),
				NULL)));
	result &= test(varbose, "cat arg1 < in1 arg2",
		astree_create_node(NODE_REDIRECTION, NULL,
			astree_create_node(NODE_CMDPATH | NODE_DATA, strdup("cat"),
				NULL,
				astree_create_node(NODE_ARGUMENT | NODE_DATA, strdup("arg1"),
					NULL,
					astree_create_node(NODE_ARGUMENT | NODE_DATA, strdup("arg2"),
						NULL,
						NULL))),
			astree_create_node(NODE_REDIRECT_LIST, NULL,
				astree_create_node(NODE_REDIRECT_IN | NODE_DATA, strdup("in1"),
					NULL,
					NULL),
				NULL)));
	// <simple command> <redirection> <token list>
	result &= test(varbose, "cat < in1 arg1 arg2",
		astree_create_node(NODE_REDIRECTION, NULL,
			astree_create_node(NODE_CMDPATH | NODE_DATA, strdup("cat"),
				NULL,
				astree_create_node(NODE_ARGUMENT | NODE_DATA, strdup("arg1"),
					NULL,
					astree_create_node(NODE_ARGUMENT | NODE_DATA, strdup("arg2"),
						NULL,
						NULL))),
			astree_create_node(NODE_REDIRECT_LIST, NULL,
				astree_create_node(NODE_REDIRECT_IN | NODE_DATA, strdup("in1"),
					NULL,
					NULL),
				NULL)));
	result &= test(varbose, "cat arg1 < in1 arg2 arg3",
		astree_create_node(NODE_REDIRECTION, NULL,
			astree_create_node(NODE_CMDPATH | NODE_DATA, strdup("cat"),
				NULL,
				astree_create_node(NODE_ARGUMENT | NODE_DATA, strdup("arg1"),
					NULL,
					astree_create_node(NODE_ARGUMENT | NODE_DATA, strdup("arg2"),
						NULL,
						astree_create_node(NODE_ARGUMENT | NODE_DATA, strdup("arg3"),
							NULL,
							NULL)))),
			astree_create_node(NODE_REDIRECT_LIST, NULL,
				astree_create_node(NODE_REDIRECT_IN | NODE_DATA, strdup("in1"),
					NULL,
					NULL),
				NULL)));
	// <simple command> <redirection list> <token>
	result &= test(varbose, "cat < in1 < in2 arg1",
		astree_create_node(NODE_REDIRECTION, NULL,
			astree_create_node(NODE_CMDPATH | NODE_DATA, strdup("cat"),
				NULL,
				astree_create_node(NODE_ARGUMENT | NODE_DATA, strdup("arg1"),
					NULL,
					NULL)),
			astree_create_node(NODE_REDIRECT_LIST, NULL,
				astree_create_node(NODE_REDIRECT_IN | NODE_DATA, strdup("in1"),
					NULL,
					NULL),
				astree_create_node(NODE_REDIRECT_LIST, NULL,
						astree_create_node(NODE_REDIRECT_IN | NODE_DATA, strdup("in2"),
							NULL,
							NULL),
						NULL))));
	result &= test(varbose, "cat arg1 < in1 < in2 arg2",
		astree_create_node(NODE_REDIRECTION, NULL,
			astree_create_node(NODE_CMDPATH | NODE_DATA, strdup("cat"),
				NULL,
				astree_create_node(NODE_ARGUMENT | NODE_DATA, strdup("arg1"),
					NULL,
					astree_create_node(NODE_ARGUMENT | NODE_DATA, strdup("arg2"),
						NULL,
						NULL))),
			astree_create_node(NODE_REDIRECT_LIST, NULL,
				astree_create_node(NODE_REDIRECT_IN | NODE_DATA, strdup("in1"),
					NULL,
					NULL),
				astree_create_node(NODE_REDIRECT_LIST, NULL,
						astree_create_node(NODE_REDIRECT_IN | NODE_DATA, strdup("in2"),
							NULL,
							NULL),
						NULL))));
	result &= test(varbose, "cat < in1 arg1 < in2",
		astree_create_node(NODE_REDIRECTION, NULL,
			astree_create_node(NODE_CMDPATH | NODE_DATA, strdup("cat"),
				NULL,
				astree_create_node(NODE_ARGUMENT | NODE_DATA, strdup("arg1"),
					NULL,
					NULL)),
			astree_create_node(NODE_REDIRECT_LIST, NULL,
				astree_create_node(NODE_REDIRECT_IN | NODE_DATA, strdup("in1"),
					NULL,
					NULL),
				astree_create_node(NODE_REDIRECT_LIST, NULL,
						astree_create_node(NODE_REDIRECT_IN | NODE_DATA, strdup("in2"),
							NULL,
							NULL),
						NULL))));
	result &= test(varbose, "cat arg1 < in1 arg2 < in2 arg3",
		astree_create_node(NODE_REDIRECTION, NULL,
			astree_create_node(NODE_CMDPATH | NODE_DATA, strdup("cat"),
				NULL,
				astree_create_node(NODE_ARGUMENT | NODE_DATA, strdup("arg1"),
					NULL,
					astree_create_node(NODE_ARGUMENT | NODE_DATA, strdup("arg2"),
						NULL,
						astree_create_node(NODE_ARGUMENT | NODE_DATA, strdup("arg3"),
							NULL,
							NULL)))),
			astree_create_node(NODE_REDIRECT_LIST, NULL,
				astree_create_node(NODE_REDIRECT_IN | NODE_DATA, strdup("in1"),
					NULL,
					NULL),
				astree_create_node(NODE_REDIRECT_LIST, NULL,
						astree_create_node(NODE_REDIRECT_IN | NODE_DATA, strdup("in2"),
							NULL,
							NULL),
						NULL))));
	// <simple command> <redirection list> <token list>
	result &= test(varbose, "cat < in1 arg1 arg2 < in2",
		astree_create_node(NODE_REDIRECTION, NULL,
			astree_create_node(NODE_CMDPATH | NODE_DATA, strdup("cat"),
				NULL,
				astree_create_node(NODE_ARGUMENT | NODE_DATA, strdup("arg1"),
					NULL,
					astree_create_node(NODE_ARGUMENT | NODE_DATA, strdup("arg2"),
						NULL,
						NULL))),
			astree_create_node(NODE_REDIRECT_LIST, NULL,
				astree_create_node(NODE_REDIRECT_IN | NODE_DATA, strdup("in1"),
					NULL,
					NULL),
				astree_create_node(NODE_REDIRECT_LIST, NULL,
						astree_create_node(NODE_REDIRECT_IN | NODE_DATA, strdup("in2"),
							NULL,
							NULL),
						NULL))));
	result &= test(varbose, "cat arg1 arg2 < in1 arg3 arg4 < in2 arg5 arg6",
		astree_create_node(NODE_REDIRECTION, NULL,
			astree_create_node(NODE_CMDPATH | NODE_DATA, strdup("cat"),
				NULL,
				astree_create_node(NODE_ARGUMENT | NODE_DATA, strdup("arg1"),
					NULL,
					astree_create_node(NODE_ARGUMENT | NODE_DATA, strdup("arg2"),
						NULL,
						astree_create_node(NODE_ARGUMENT | NODE_DATA, strdup("arg3"),
							NULL,
							astree_create_node(NODE_ARGUMENT | NODE_DATA, strdup("arg4"),
								NULL,
								astree_create_node(NODE_ARGUMENT | NODE_DATA, strdup("arg5"),
									NULL,
									astree_create_node(NODE_ARGUMENT | NODE_DATA, strdup("arg6"),
										NULL,
										NULL))))))),
			astree_create_node(NODE_REDIRECT_LIST, NULL,
				astree_create_node(NODE_REDIRECT_IN | NODE_DATA, strdup("in1"),
					NULL,
					NULL),
				astree_create_node(NODE_REDIRECT_LIST, NULL,
						astree_create_node(NODE_REDIRECT_IN | NODE_DATA, strdup("in2"),
							NULL,
							NULL),
						NULL))));
	result &= test(varbose, "cat arg1 arg2 > out1 arg3 arg4 > out2 arg5 arg6",
		astree_create_node(NODE_REDIRECTION, NULL,
			astree_create_node(NODE_CMDPATH | NODE_DATA, strdup("cat"),
				NULL,
				astree_create_node(NODE_ARGUMENT | NODE_DATA, strdup("arg1"),
					NULL,
					astree_create_node(NODE_ARGUMENT | NODE_DATA, strdup("arg2"),
						NULL,
						astree_create_node(NODE_ARGUMENT | NODE_DATA, strdup("arg3"),
							NULL,
							astree_create_node(NODE_ARGUMENT | NODE_DATA, strdup("arg4"),
								NULL,
								astree_create_node(NODE_ARGUMENT | NODE_DATA, strdup("arg5"),
									NULL,
									astree_create_node(NODE_ARGUMENT | NODE_DATA, strdup("arg6"),
										NULL,
										NULL))))))),
			astree_create_node(NODE_REDIRECT_LIST, NULL,
				astree_create_node(NODE_REDIRECT_OUT | NODE_DATA, strdup("out1"),
					NULL,
					NULL),
				astree_create_node(NODE_REDIRECT_LIST, NULL,
						astree_create_node(NODE_REDIRECT_OUT | NODE_DATA, strdup("out2"),
							NULL,
							NULL),
						NULL))));
	result &= test(varbose, "cat arg1 arg2 >> out1 arg3 arg4 >> out2 arg5 arg6",
		astree_create_node(NODE_REDIRECTION, NULL,
			astree_create_node(NODE_CMDPATH | NODE_DATA, strdup("cat"),
				NULL,
				astree_create_node(NODE_ARGUMENT | NODE_DATA, strdup("arg1"),
					NULL,
					astree_create_node(NODE_ARGUMENT | NODE_DATA, strdup("arg2"),
						NULL,
						astree_create_node(NODE_ARGUMENT | NODE_DATA, strdup("arg3"),
							NULL,
							astree_create_node(NODE_ARGUMENT | NODE_DATA, strdup("arg4"),
								NULL,
								astree_create_node(NODE_ARGUMENT | NODE_DATA, strdup("arg5"),
									NULL,
									astree_create_node(NODE_ARGUMENT | NODE_DATA, strdup("arg6"),
										NULL,
										NULL))))))),
			astree_create_node(NODE_REDIRECT_LIST, NULL,
				astree_create_node(NODE_REDIRECT_OUT2 | NODE_DATA, strdup("out1"),
					NULL,
					NULL),
				astree_create_node(NODE_REDIRECT_LIST, NULL,
						astree_create_node(NODE_REDIRECT_OUT2 | NODE_DATA, strdup("out2"),
							NULL,
							NULL),
						NULL))));
	// error
	// error_test(varbose, "cat < <", "syntax error near unexpected token `<'");
	// 	test("cat < out test;;"); // ';;'
	// 	test("cat < ;"); // ';'
	// 	// error
	// 	test("echo >"); // 'newline';
	// /*
	//  * <redirection> ::= '<<' <token> <token list>
	//  */
	// // test("cat << test");
	// 	// error
	// 	test("echo >>"); // 'newline';

	/*
	 * <command line> ::= <job>
	 * <job> ::= <command>
	 * <job> ::= <command> '|' <job>
	 */
	result &= test(varbose, "echo arg1 | tr a A",
		astree_create_node(NODE_PIPE, NULL,
			astree_create_node(NODE_CMDPATH | NODE_DATA, strdup("echo"),
				NULL,
				astree_create_node(NODE_ARGUMENT | NODE_DATA, strdup("arg1"),
					NULL,
					NULL)),
			astree_create_node(NODE_CMDPATH | NODE_DATA, strdup("tr"),
					NULL,
					astree_create_node(NODE_ARGUMENT | NODE_DATA, strdup("a"),
						NULL,
						astree_create_node(NODE_ARGUMENT | NODE_DATA, strdup("A"),
							NULL,
							NULL)))));
	result &= test(varbose, "a | b | c",
		astree_create_node(NODE_PIPE, NULL,
			astree_create_node(NODE_CMDPATH | NODE_DATA, strdup("a"),
				NULL,
				NULL),
			astree_create_node(NODE_PIPE, NULL,
				astree_create_node(NODE_CMDPATH | NODE_DATA, strdup("b"),
					NULL,
					NULL),
				astree_create_node(NODE_CMDPATH | NODE_DATA, strdup("c"),
					NULL,
					NULL))));
	// 	//error
	// 	test("a |"); // '|'
	// /*
	//  * <command line> ::= <job> ;
	//  * <command line> ::= <job> ; <command line>
	//  */
	// test(true, "a;", NULL);
	// test(true, "a; b; c" NULL);
	// 	//error
	// 	test("echo a;;"); // ';;'
	// 	test("echo a;; ;"); // ';;'
	// /*
	//  * <command line> ::= <job> & // not make
	//  * <command line> ::= <job> & <command line> // not make
	//  */
	return (!result);
}
