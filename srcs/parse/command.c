#include "parse.h"

t_astree	*cmd1(t_list **toks); // <simple command> <redirection list>
t_astree	*cmd2(t_list **toks); // <simple command>
void		collect_args(t_astree *simplecmd_node, t_astree *redirlist_node);

/**
 * @brief <command>	::= <simple command> <redirection list>
 *					  | <simple command>
 */
t_astree	*cmd(t_list **toks)
{
	t_list		*save;
	t_astree	*result;

	save = *toks;
	result = cmd1(toks);
	if (result != NULL)
		return (result);
	*toks = save;
	return (cmd2(toks));
}

/**
 * <command> ::= <simple command> <redirection list>
 */
t_astree	*cmd1(t_list **toks)
{
	t_astree	*simplecmd_node;
	t_astree	*redirlist_node;
	t_astree	*result;

	simplecmd_node = simplecmd(toks);
	if (simplecmd_node == NULL)
		return (NULL);
	redirlist_node = redirlist(toks);
	if (redirlist_node == NULL)
		return (astree_delete_node(simplecmd_node));
	collect_args(simplecmd_node, redirlist_node);
	return (astree_create_node(NODE_REDIRECTION, NULL,
			simplecmd_node, redirlist_node));
}

/**
 * <command> ::= <simple command>
 */
t_astree	*cmd2(t_list **toks)
{
	return (simplecmd(toks));
}

void	collect_args(t_astree *simplecmd_node, t_astree *redirlist_node)
{
	t_astree	*args;

	while (redirlist_node != NULL)
	{
		args = redirlist_node->left->right;
		astree_get_right_last(simplecmd_node)->right = args;
		redirlist_node->left->right = NULL;
		redirlist_node = redirlist_node->right;
	}
}
