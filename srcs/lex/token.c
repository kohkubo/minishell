#include "../../includes/lex.h"

void	token_end(t_lexer *lexer, t_tok **tok, size_t n)
{
	if (n > 0)
	{
		ft_lstadd_back(&lexer->listtok, ft_lstnew(*tok));
		lexer->len++;
	}
}

void	token_end_and_create(t_lexer *lexer, t_tok **tok, char *s, size_t *n)
{
	if (n == NULL)
	{
		token_end(lexer, tok, 1);
		*tok = tok_init(s);
	}
	else if (*n > 0)
	{
		token_end(lexer, tok, 1);
		*tok = tok_init(s);
		*n = 0;
	}
}

void	token_store_and_create(t_lexer *l, t_tok **t, char *s, t_token_type typ)
{
	t_tok	*tmp;

	tmp = *t;
	tmp->data[0] = *s;
	tmp->data[1] = 0;
	tmp->type = typ;
	token_end_and_create(l, t, s, NULL);
}
