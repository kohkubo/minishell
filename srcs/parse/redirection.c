#include "parse.h"

t_astree	*redirection1(
				t_list **toks, t_token_type t, t_node_type n, bool *has_error);

/**
<redirection>		::= '<' <filename>
					  | '>' <filename>
					  | '<<' <filename>
					  | '>>' <filename>
*/
t_astree	*redirection(t_list **toks, bool *has_error)
{
	t_list		*save;
	t_astree	*result;

	save = *toks;
	result = redirection1(toks, CHAR_LESSER, NODE_REDIRECT_IN, has_error);
	if (result != NULL || *has_error)
		return (result);
	*toks = save;
	result = redirection1(toks, CHAR_GREATER, NODE_REDIRECT_OUT, has_error);
	if (result != NULL || *has_error)
		return (result);
	*toks = save;
	result = redirection1(toks, CHAR_LESSER2, NODE_REDIRECT_IN2, has_error);
	if (result != NULL || *has_error)
		return (result);
	*toks = save;
	return (redirection1(toks, CHAR_GREATER2, NODE_REDIRECT_OUT2, has_error));
}

t_astree	*redirection1(
				t_list **toks, t_token_type t, t_node_type n, bool *has_error)
{
	char		*filename;

	if (!move_if_is_tokentype(t, toks))
		return (NULL);
	if (!allocate_data_if_is_token(toks, &filename))
	{
		*has_error = true;
		return (NULL);
	}
	return (astree_create_node(n | NODE_DATA, filename, NULL, NULL));
}
