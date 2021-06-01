#include "../../includes/lex.h"

t_token_type	token_type(char c)
{
	if (c == '|')
		return (c);
	if (c == '\'')
		return (c);
	if (c == '"')
		return (c);
	if (c == ';')
		return (c);
	if (c == '\\')
		return (c);
	if (c == '>')
		return (c);
	if (c == '<')
		return (c);
	if (c == '<')
		return (c);
	if (ft_isspace(c))
		return (' ');
	if (c == 0)
		return (c);
	else
		return (CHAR_GENERAL);
}

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
