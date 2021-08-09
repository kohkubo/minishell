#include "parse.h"

t_astree	*redirlist1(t_list **toks);

/**
 * <redirection list> ::= <redirection> <redirection list>
 */
t_astree	*redirlist(t_list **toks)
{
	return (redirlist1(toks));
}

/**
 * <redirection list> ::= <redirection> <redirection list>
 */
t_astree	*redirlist1(t_list **toks)
{
	t_astree	*redirection_node;
	t_astree	*redirlist_node;

	redirection_node = redirection(toks);
	if (redirection_node == NULL)
		return (NULL);
	redirlist_node = redirlist(toks);
	if (redirlist_node == NULL)
		return (astree_delete_node(redirection_node));
	return (astree_create_node(NODE_REDIRECT_LIST, NULL,
			redirection_node, redirlist_node));
}
