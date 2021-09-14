#include "lex.h"

t_tok	*tok_init(char *s)
{
	size_t	len;
	t_tok	*tok;

	tok = ft_xcalloc(sizeof(t_tok), 1);
	len = ft_strlen(s) + 1;
	tok->data = ft_xcalloc(len, 1);
	return (tok);
}

t_tok	*new_tok(t_token_type type, char *data)
{
	t_tok	*tok;

	tok = ft_xmalloc(sizeof(t_tok));
	tok->data = data;
	tok->type = type;
	return (tok);
}

t_lexer	*lexer_init(void)
{
	t_lexer	*lexer;

	lexer = ft_xcalloc(sizeof(t_lexer), 1);
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
