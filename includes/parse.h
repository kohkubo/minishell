#ifndef PARSE_H
# define PARSE_H
# include "shell.h"
# include "astree.h"

bool		is_tokentype(t_token_type type, t_list **current);
t_astree	*cmdline(t_list **toks);
t_astree	*job(t_list **toks);
t_astree	*cmd(t_list **toks);
t_astree	*simplecmd(t_list **toks);
t_astree	*tokenlist(t_list **toks);

#endif
