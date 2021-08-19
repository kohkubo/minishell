#include "parse.h"

t_astree	*simplecmd1(t_list **toks); // <pathname> <token list>

/**
 * @brief <simple command>::= <pathname> <token list>
 */
t_astree	*simplecmd(t_list **toks)
{
	return (simplecmd1(toks));
}

/**
 * @brief <simple command>::= <pathname> <token list>
 */
t_astree	*simplecmd1(t_list **toks)
{
	t_astree	*tokenlist_node;
	char		*pathname;

	if (!is_tokentype_and_store_data(TOKEN, toks, &pathname))
		return (NULL);
	tokenlist_node = tokenlist(toks);
	return (astree_create_node(NODE_CMDPATH | NODE_DATA, pathname,
			NULL, tokenlist_node));
}
