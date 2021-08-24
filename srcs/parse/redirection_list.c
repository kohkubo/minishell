#include "parse.h"

t_astree	*redirlist1(t_list **toks); // <redirection> <redirection list>
t_astree	*redirlist2(t_list **toks); // <redirection>

/**
 * <redirection list> ::= <redirection> <redirection list>
 * 						| <redirection>
 */
t_astree	*redirlist(t_list **toks)
{
	t_list		*save;
	t_astree	*node;

	save = *toks;
	node = redirlist1(toks);
	if (node != NULL)
		return (node);
	*toks = save;
	return (redirlist2(toks));
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

/**
 * <redirection list> ::= <redirection>
 */
t_astree	*redirlist2(t_list **toks)
{
	t_astree	*redirection_node;

	redirection_node = redirection(toks);
	if (redirection_node == NULL)
		return (NULL);
	return (astree_create_node(NODE_REDIRECT_LIST, NULL,
			redirection_node, NULL));
}
