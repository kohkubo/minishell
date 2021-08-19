#include "parse.h"

t_astree	*redirection1(t_list **toks, t_token_type t, t_node_type n);
t_astree	*redirection2(t_list **toks);

/**
<redirection>		::= '<' <filename> <token list>
					  | '>' <filename> <token list>
					  | '<<' <token>
					  | '>>' <filename> <token list>
// <token list> will be added after the arg of the previous <simple command>.
*/
t_astree	*redirection(t_list **toks)
{
	t_list		*save;
	t_astree	*result;

	save = *toks;
	result = redirection1(toks, CHAR_LESSER, NODE_REDIRECT_IN);
	if (result != NULL)
		return (result);
	*toks = save;
	result = redirection1(toks, CHAR_GREATER, NODE_REDIRECT_OUT);
	if (result != NULL)
		return (result);
	*toks = save;
	result = redirection2(toks);
	if (result != NULL)
		return (result);
	*toks = save;
	return (redirection1(toks, CHAR_GREATER2, NODE_REDIRECT_OUT2));
}

t_astree	*redirection1(t_list **toks, t_token_type t, t_node_type n)
{
	t_astree	*tokenlist_node;
	char		*filename;

	if (!is_tokentype_and_store_data(t, toks, NULL))
		return (NULL);
	if (!is_tokentype_and_store_data(TOKEN, toks, &filename))
		return (NULL);
	tokenlist_node = tokenlist(toks);
	return (astree_create_node(n | NODE_DATA, filename, NULL, tokenlist_node));
}

t_astree	*redirection2(t_list **toks)
{
	char		*doc;

	if (!is_tokentype_and_store_data(CHAR_LESSER2, toks, NULL))
		return (NULL);
	if (!is_tokentype_and_store_data(TOKEN, toks, &doc))
		return (NULL);
	return (astree_create_node(NODE_REDIRECT_IN2 | NODE_DATA, doc, NULL, NULL));
}
