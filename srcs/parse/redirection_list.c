#include "parse.h"

t_astree	*redirlist1(t_list **toks, bool *has_error);

/**
 * <redirection list> ::= <redirection> <redirection list>
 */
t_astree	*redirlist(t_list **toks, bool *has_error)
{
	return (redirlist1(toks, has_error));
}

/**
 * <redirection list> ::= <redirection> <redirection list>
 */
t_astree	*redirlist1(t_list **toks, bool *has_error)
{
	t_astree	*redirection_node;
	t_astree	*redirlist_node;

	redirection_node = redirection(toks, has_error);
	if (redirection_node == NULL)
		return (NULL);
	redirlist_node = redirlist(toks, has_error);
	return (astree_create_node(NODE_REDIRECT_LIST, NULL,
			redirection_node, redirlist_node));
}
