#include "parse.h"

t_astree	*tokenlist1(t_list **toks, bool *has_error); // <token> <token list>
t_astree	*tokenlist2(t_list **toks, bool *has_error); // (EMPTY)

/**
 * <token list>	::= <token> <token list>
 *				  | <token>
 */
t_astree	*tokenlist(t_list **toks, bool *has_error)
{
	t_list		*save;
	t_astree	*node;

	save = *toks;
	node = tokenlist1(toks, has_error);
	if (node != NULL || *has_error)
		return (node);
	*toks = save;
	return (tokenlist2(toks, has_error));
}

t_astree	*tokenlist1(t_list **toks, bool *has_error)
{
	t_astree	*tokenlist_node;
	char		*arg;

	if (!allocate_data_if_is_token(toks, &arg))
		return (NULL);
	tokenlist_node = tokenlist(toks, has_error);
	if (tokenlist_node == NULL)
	{
		free(arg);
		return (NULL);
	}
	return (astree_create_node(NODE_ARGUMENT | NODE_DATA, arg,
			NULL, tokenlist_node));
}

t_astree	*tokenlist2(t_list **toks, bool *has_error)
{
	char		*arg;

	(void)has_error;
	if (!allocate_data_if_is_token(toks, &arg))
		return (NULL);
	return (astree_create_node(NODE_ARGUMENT | NODE_DATA, arg, NULL, NULL));
}
