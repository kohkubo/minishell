#include "parse.h"

// <pathname> <token list>
t_astree	*simplecmd1(t_list **toks, bool *has_error);

/**
 * @brief <simple command>::= <pathname> <token list>
 */
t_astree	*simplecmd(t_list **toks, bool *has_error)
{
	return (simplecmd1(toks, has_error));
}

/**
 * @brief <simple command>::= <pathname> <token list>
 */
t_astree	*simplecmd1(t_list **toks, bool *has_error)
{
	t_astree	*tokenlist_node;
	char		*pathname;

	if (!allocate_data_if_is_token(toks, &pathname))
		return (NULL);
	tokenlist_node = tokenlist(toks, has_error);
	return (astree_create_node(NODE_CMDPATH | NODE_DATA, pathname,
			NULL, tokenlist_node));
}
