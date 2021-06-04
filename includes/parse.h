#ifndef PARSE_H
# define PARSE_H
# include "libft.h"
# include "astree.h"
# include "lex.h"

bool		is_tokentype(t_token_type type, t_list **current, char **buf_ptr);
t_astree	*cmdline(t_list **toks);
t_astree	*job(t_list **toks);
t_astree	*cmd(t_list **toks);
t_astree	*simplecmd(t_list **toks);
t_astree	*tokenlist(t_list **toks);

#endif
