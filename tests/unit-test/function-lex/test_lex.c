#include "./../../../includes/shell.h"
#include "./../../../includes/lex.h"
#include "./../../../libft/libft/libft.h"
#include "./../../../libft/libex/libex.h"
#include "./../../../libft/libhash/libhash.h"
#include "./../../../libft/libdebug/libdebug.h"
#include <libc.h>

void	display_lexer(void *content)
{
	t_tok	*tok;

	tok = (t_tok *)content;
	printf("%s : %d\n", tok->data, tok->type);
}

void	lexer_free(void *content)
{
	t_tok	*tok;

	tok = (t_tok *)content;
	free(tok->data);
	free(tok);
}


void test(char *s)
{
	t_lexer	*lexer;

	printf(" === test === \n");
	printf("s : %s\n", s);
	lexer = minishell_lexer(s);
	ft_lstiter(lexer->listtok, display_lexer);
	ft_lstclear(&lexer->listtok, lexer_free);
	free(lexer);
}

int main(void)
{
	// test("echo test test");
	test("      echo     test      test    ");
	// test("   echo test test");
	// test("echo test test  ");
	// test("echo test ;test");
	// test("echo test |test");
	// test("echo test >test");
	// test("echo test < test");
	// test("echo test >> test");
	// test("echo test << test");
	// test("'echo test << test'");
	// test("echo 'echo test << test'");
	// test("'echo test << test' eeee");
	// test("aa 'echo test << test' eeee");
	// test("'echo test << test''sssssssssssss'");
	// test("'echo test << test'\"sssssssssssss\"");
	// test("\"echo ssssss\"");
	// test("echo test ;\n\taaaaa");
	// test("echo test ;;");
}
