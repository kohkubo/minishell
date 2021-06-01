#ifndef LEX_H
# define LEX_H

# include "shell.h"

bool			\
minishell_lexer3(t_tok **tok, t_state *state, char **s, size_t *i);
void			\
minishell_lexer4(t_lexer *lexer, t_tok **tok, char **s, size_t *i);
void			\
minishell_lexer5(t_tok *tok, t_state *state, char *s, size_t *i);
void			minishell_lexer2(t_lexer *lexer, t_tok *tok, char *s);
t_lexer			*minishell_lexer(char *s);
void			token_end(t_lexer *lexer, t_tok **tok, size_t n);
void			\
token_end_and_create(t_lexer *lexer, t_tok **tok, char *s, size_t *n);
void			\
token_store_and_create(t_lexer *l, t_tok **t, char *s, t_token_type typ);
int				ft_cmp(char a, char *str);
t_token_type	token_type(char c);
t_tok			*tok_init(char *s);
t_lexer			*lexer_init(void);

#endif
