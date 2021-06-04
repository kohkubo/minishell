#include "parse.h"

t_astree	*cmd_redirect(t_list **toks, t_token_type t, t_node_type n);
t_astree	*cmd1(t_list **toks); // <simple command>

/**
 * <command>	::= <simple command> '<' <filename>
 *				  | <simple command> '>' <filename>
 *				  | <simple command> '<<' <filename>
 *				  | <simple command> '>>' <filename>
 *				  | <simple command>
 */
t_astree	*cmd(t_list **toks)
{
	t_list		*save;
	t_astree	*result;

	save = *toks;
	result = cmd_redirect(toks, CHAR_LESSER, NODE_REDIRECT_IN);
	if (result != NULL)
		return (result);
	*toks = save;
	result = cmd_redirect(toks, CHAR_GREATER, NODE_REDIRECT_OUT);
	if (result != NULL)
		return (result);
	*toks = save;
	result = cmd_redirect(toks, CHAR_LESSER2, NODE_REDIRECT_IN2);
	if (result != NULL)
		return (result);
	*toks = save;
	result = cmd_redirect(toks, CHAR_GREATER2, NODE_REDIRECT_OUT2);
	if (result != NULL)
		return (result);
	*toks = save;
	return (cmd1(toks));
}

/**
 * <command> ::= <simple command> t <filename>
 */
t_astree	*cmd_redirect(t_list **toks, t_token_type t, t_node_type n)
{
	t_astree	*simplecmd_node;
	t_astree	*result;
	char		*filename;

	simplecmd_node = simplecmd(toks);
	if (simplecmd_node == NULL)
		return (NULL);
	if (!is_tokentype(t, toks, NULL)) {
		return (astree_delete_node(simplecmd_node));
	}
	if (!is_tokentype(TOKEN, toks, &filename))
		return (astree_delete_node(simplecmd_node));
	return (astree_create_node(n | NODE_DATA, filename, NULL, simplecmd_node));
}

/**
 * <command> ::= <simple command>
 */
t_astree	*cmd1(t_list **toks)
{
	return (simplecmd(toks));
}
