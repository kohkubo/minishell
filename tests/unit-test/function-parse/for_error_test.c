#include <stdio.h>
#include "shell.h"
#include "lex.h"
#include "logging.h"

t_shell	g_shell = {};

t_tok	*new_token(char *data, t_token_type	type)
{
	t_tok	*ret;

	ret = malloc(sizeof(t_tok));
	if (data)
		ret->data = ft_strdup(data);
	else
		ret->data = NULL;
	ret->type = type;
	return (ret);
}

bool	test(t_tok **toks)
{
	t_lexer		*lex;
	t_astree	*tree;
	bool		isSuccess;
	char		*str;

	lex = lexer_init();
	g_shell.exit_status = 0;
	str = ft_strdup("");
	while (*toks)
	{
		ft_lstadd_back(&lex->listtok, ft_lstnew(new_token((*toks)->data, (*toks)->type)));
		free_set((void **)&str, ft_strjoin(str, (*toks)->data));
		free_set((void **)&str, ft_strjoin(str, " "));
		toks++;
	}
	isSuccess = parse_v2(lex, &tree);
	lexer_free(&lex);
	tree = astree_delete_node(tree);
	printf("%s(%d)%s\n", str, g_shell.exit_status, (!isSuccess && g_shell.exit_status == 258) ? GREEN"✓"END : RED"×"END);
	free(str);
	return (!isSuccess && g_shell.exit_status == 258);
}

int	main(int argc, char *argv[])
{
	bool		result;

	result = true;
	/**
	 * a |
	 */
	result &= test((t_tok *[]){
		&(t_tok){.data = "a", .type = TOKEN},
		&(t_tok){.data = "|", .type = CHAR_PIPE},
		NULL
	});
	/**
	 * a | |
	 */
	result &= test((t_tok *[]){
		&(t_tok){.data = "a", .type = TOKEN},
		&(t_tok){.data = "|", .type = CHAR_PIPE},
		&(t_tok){.data = "|'", .type = CHAR_PIPE},
		NULL
	});
	/**
	 * a >
	 */
	result &= test((t_tok *[]){
		&(t_tok){.data = "a", .type = TOKEN},
		&(t_tok){.data = ">", .type = CHAR_GREATER},
		NULL
	});
	/**
	 * a >> >
	 */
	result &= test((t_tok *[]){
		&(t_tok){.data = "a", .type = TOKEN},
		&(t_tok){.data = ">>", .type = CHAR_GREATER2},
		&(t_tok){.data = ">", .type = CHAR_GREATER},
		NULL
	});
	/**
	 * a ; ;;
	 */
	result &= test((t_tok *[]){
		&(t_tok){.data = "a", .type = TOKEN},
		&(t_tok){.data = ";", .type = ';'},
		&(t_tok){.data = ";;", .type = ';' + 128},
		NULL
	});
	return (!result);
}
