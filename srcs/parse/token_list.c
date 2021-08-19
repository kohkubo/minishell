#include "parse.h"

t_astree	*tokenlist1(t_list **toks); // <token> <token list>
t_astree	*tokenlist2(t_list **toks); // (EMPTY)

/**
 * <token list>	::= <token> <token list>
 *				  | (EMPTY)
 */
t_astree	*tokenlist(t_list **toks)
{
	t_astree	*node;

	node = tokenlist1(toks);
	if (node != NULL)
		return (node);
	return (tokenlist2(toks));
}

t_astree	*tokenlist1(t_list **toks)
{
	t_astree	*tokenlist_node;
	char		*arg;

	if (!is_tokentype_and_store_data(TOKEN, toks, &arg))
		return (NULL);
	tokenlist_node = tokenlist(toks);
	return (astree_create_node(NODE_ARGUMENT | NODE_DATA, arg,
			NULL, tokenlist_node));
}

t_astree	*tokenlist2(t_list **toks)
{
	return (NULL);
}