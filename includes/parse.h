#ifndef PARSE_H
# define PARSE_H
# include "libft.h"
# include "astree.h"
# include "lex.h"

bool		move_if_is_tokentype(t_token_type type, t_list **current);
bool		allocate_data_if_is_token(t_list **current, char **buf_ptr);
t_astree	*cmdline(t_list **toks, bool *has_error);
t_astree	*job(t_list **toks, bool *has_error);
t_astree	*cmd(t_list **toks, bool *has_error);
t_astree	*redirlist(t_list **toks, bool *has_error);
t_astree	*redirection(t_list **toks, bool *has_error);
t_astree	*simplecmd(t_list **toks, bool *has_error);
t_astree	*tokenlist(t_list **toks, bool *has_error);

#endif
