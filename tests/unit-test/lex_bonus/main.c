#include "shell.h"
#include "lex.h"
#include "libft.h"
#include "libex.h"
#include "libhash.h"
#include <libc.h>

t_shell	g_shell;

void	display_lexer(void *content)
{
	t_tok	*tok;

	tok = (t_tok *)content;
	printf("%s : %d\n", tok->data, tok->type);
}

void test(char *s)
{
	t_lexer	*lexer;

	printf(" === test ===\n");
	printf("s : %s\n", s);
	minishell_lexer(s, &lexer);
	if (lexer == NULL)
	{
		printf("NULL!\n");
		return ;
	}
	printf("lexer->len : %d\n", lexer->len);
	ft_lstiter(lexer->listtok, display_lexer);
	lexer_free(&lexer);
}

int main(void)
{
	printf("\n&& && &&\n");
	test("echo aaa && echo bbb");
	test("echo aaa &&");
	test("&& echo aaa");
	test("&&");
	test(" &&");
	test("&& ");
	test(" && ");
	test("&& &&");
	test("&& && &&");
	test("&&&");
	test("&&&&");
	test("ls&&ls");
	test("ls&&ls&&");
	test("&&ls&&ls");
	test("&ls&");
	test("&");
	test("&ls");
	test("& ls");
	test("ls&");
	test("ls               &                       &ls");

	printf("\n|| || ||\n");
	test("echo aaa || echo bbb");
	test("echo aaa ||");
	test("|| echo aaa");
	test("||");
	test(" ||");
	test("|| ");
	test(" || ");
	test("|| ||");
	test("|| || ||");
	test("|||");
	test("||||");
	test("ls||ls");
	test("ls||ls||");
	test("||ls||ls");

	test("echo test aiueo");
	test("      echo     test      aiueo    ");
	test("   echo test aiueo");
	test("echo test aiueo  ");

	// printf("\n; ; ;\n");
	// test("echo test;aiueo");
	// test("echo test; aiueo");
	// test("echo test ;aiueo");
	// test("echo test ; aiueo");
	// test("echo test;");
	// test("echo test ;");
	// test("echo test; ");

	printf("\n| | |\n");
	test("echo test|aiueo");
	test("echo test| aiueo");
	test("echo test |aiueo");
	test("echo test | aiueo");
	test("echo test|");
	test("echo test |");
	test("echo test| ");

	printf("\n> > >\n");
	test("echo test>aiueo");
	test("echo test> aiueo");
	test("echo test >aiueo");
	test("echo test > aiueo");
	test("echo test>");
	test("echo test >");
	test("echo test> ");

	printf("\n< < <\n");
	test("echo test<aiueo");
	test("echo test< aiueo");
	test("echo test <aiueo");
	test("echo test < aiueo");
	test("echo test<");
	test("echo test <");
	test("echo test< ");

	printf("\n>> >> >>\n");
	test("echo test>>aiueo");
	test("echo test>> aiueo");
	test("echo test >>aiueo");
	test("echo test >> aiueo");
	test("echo test>>");
	test("echo test >>");
	test("echo test>> ");

	// printf("\n<< << <<\n");
	// test("echo test<<aiueo");
	// test("echo test<< aiueo");
	// test("echo test <<aiueo");
	// test("echo test << aiueo");
	// test("echo test<<");
	// test("echo test <<");
	// test("echo test<< ");

	printf("\n' ' '\n");
	test("'echo test << aiueo'");
	test("echo 'echo test << aiueo'");
	test("'echo test << test' eeee");
	test("aa 'echo test << test' eeee");
	test("'echo test << test''sssssssssssss'");
	test("'echo \"test\"'");
	test("'echo \\' test");
	test("'\\n'");

	// printf("\n'\" '\" '\"\n");
	// test("'echo test << test'\"sssssssssssss\"");

	printf("\n\" \" \"\n");
	test("\"echo ssssss\"");
	test("\"echo 'ssssss'\"");

	// printf("\n;; ;; ;;\n");
	// test("echo test ;;");
	// test(";;");

	// printf("\n\\ \\ \\\n");
	// // test("echo test ;\n\taaaaa");
	// test("\\\\");
	// test("echo \\\\");
	// test("echo test\\\\");
	// test("aiueo\\ ssssssssss");
	// test("aiueo \\ssssssssss");
	// test("aiueo \\ ssssssssss");
	// test("aiueo\\ssssssssss");
	// test("aiueo\\\\ssssssssss");

	printf("\nその他\n");
	test(" ");
	test("           ");
	test("echo -n");
	test("echo -n test");

	// printf("\nNULL test\n");
	// test("'test''");
	// test("\"test\"\"");
	// test("'''");
	// test("''' ");
	// test("'' '");
	// test("'' ' ");
	// test("\"\"\"");
	// test("\"\" \"");
	// test("\"\"\" ");
	// test("\"\" \" ");
	// test("\"\" \" >");
	// test("\"\" \" aaa");
	// test("\"\" \" >>");
	// test("\"\" \" >>>");
	// test("\"\" \">>>");
	// test("'");
	// test("\"");
	// test("\\");
	// test("\\\\\\");
	// test("aiueo\\");

	// printf("\n\\\" \\\" \\\"\n");
	// test("\"echo \\\"test\\\"\"");
	// test("\"echo \\\"test\\\"\" a");
	// test("\"echo \\\"test\\\"\"a ");
	// test("\"echo \\\"test\\\"\" a ");
	// test("\"echo \\\"test\\\"\"a");
	// test("tatata\"  aiueo  \"test");
	// test("\\\'");
	// test("\\\" \\\"");
	// test("\\\"");
	// test("\"\\\"\"");
	// test("\" \\\" \"");
	// test("\" \\\" \\\" \"");
}
