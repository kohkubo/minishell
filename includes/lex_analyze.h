#ifndef LEX_ANALYZE_H
# define LEX_ANALYZE_H

# include "lex.h"

void			token_end(t_lexer *lexer, t_tok **tok, size_t n);
void			\
token_end_and_create(t_lexer *lexer, t_tok **tok, char *s, size_t *n);
void			\
token_store_and_create(t_lexer *l, t_tok **t, char *s, t_token_type typ);
t_token_type	token_type(char c);

#endif
