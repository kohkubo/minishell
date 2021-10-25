#include "parse.h"

t_astree	*cmd_token(t_list **toks, bool *has_error);
t_astree	*cmd_redirection(t_list **toks, bool *has_error);
t_astree	*cmd_empty(t_list **toks, bool *has_error);

/**
 * <command>	::= <token list> <command>
 * 				  | <redirection> <command>
 * 				  | (EMPTY)
 */
t_astree	*cmd(t_list **toks, bool *has_error)
{
	t_list		*save;
	t_astree	*result;

	save = *toks;
	result = cmd_token(toks, has_error);
	if (result != NULL || *has_error)
		return (result);
	*toks = save;
	result = cmd_redirection(toks, has_error);
	if (result != NULL || *has_error)
		return (result);
	*toks = save;
	return (cmd_empty(toks, has_error));
}

t_astree	*cmd_token(t_list **toks, bool *has_error)
{
	t_astree	*token_node;
	t_astree	*cmd_node;
	t_astree	*tmp;

	token_node = tokenlist(toks, has_error);
	if (token_node == NULL)
		return (NULL);
	token_node->type = NODE_CMDPATH | NODE_DATA;
	cmd_node = cmd(toks, has_error);
	if (cmd_node == NULL)
		return (token_node);
	if (cmd_node->type & NODE_REDIRECTION)
	{
		cmd_node->left->type = NODE_ARGUMENT | NODE_DATA;
		astree_get_right_last(token_node)->right = cmd_node->left;
		cmd_node->left = NULL;
		tmp = cmd_node->right;
		cmd_node->right = NULL;
		astree_delete_node(cmd_node);
		cmd_node = tmp;
	}
	return (astree_create_node(NODE_REDIRECTION, NULL,
			token_node, cmd_node));
}

t_astree	*cmd_redirection(t_list **toks, bool *has_error)
{
	t_astree	*redirection_node;
	t_astree	*cmd_node;
	t_astree	*tmp;

	redirection_node = redirlist(toks, has_error);
	if (redirection_node == NULL)
		return (NULL);
	cmd_node = cmd(toks, has_error);
	if (cmd_node == NULL)
		return (redirection_node);
	if (cmd_node->type & NODE_REDIRECTION)
	{
		cmd_node->left->type = NODE_ARGUMENT | NODE_DATA;
		astree_get_right_last(redirection_node)->right = cmd_node->right;
		cmd_node->right = NULL;
		tmp = cmd_node->left;
		cmd_node->left = NULL;
		astree_delete_node(cmd_node);
		cmd_node = tmp;
	}
	cmd_node->type = NODE_CMDPATH | NODE_DATA;
	return (astree_create_node(NODE_REDIRECTION, NULL,
			cmd_node, redirection_node));
}

t_astree	*cmd_empty(t_list **toks, bool *has_error)
{
	(void)toks;
	(void)has_error;
	return (NULL);
}
