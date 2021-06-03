#include "../../includes/lex_analyze.h"

t_tok	*tok_init(char *s)
{
	size_t	len;
	t_tok	*tok;

	tok = ft_xmalloc(sizeof(t_tok));
	len = ft_strlen(s) + 1;
	tok->data = ft_xmalloc(len);
	ft_bzero((void *)tok->data, len);
	tok->type = 0;
	return (tok);
}

t_lexer	*lexer_init(void)
{
	t_lexer	*lexer;

	lexer = ft_xmalloc(sizeof(t_lexer));
	lexer->len = 0;
	lexer->listtok = NULL;
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
