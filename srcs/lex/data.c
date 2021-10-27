#include "lex.h"

t_tok	*tok_new(char *data, t_token_type type)
{
	t_tok	*tok;

	tok = ft_xmalloc(sizeof(t_tok));
	tok->data = ft_xstrdup(data);
	tok->type = type;
	return (tok);
}

t_lexer	*lexer_new(t_list *listtok)
{
	t_lexer	*lexer;

	lexer = ft_xcalloc(sizeof(t_lexer), 1);
	lexer->len = ft_lstsize(listtok);
	lexer->listtok = listtok;
	return (lexer);
}

void	tok_free(void *content)
{
	t_tok	*tok;

	tok = (t_tok *)content;
	free(tok->data);
	tok->data = NULL;
	free(tok);
}

void	lexer_free(t_lexer **lexer)
{
	ft_lstclear(&(*lexer)->listtok, tok_free);
	free(*lexer);
	*lexer = NULL;
}
