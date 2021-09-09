#include "parse.h"

t_astree	*job1(t_list **toks, bool *has_error); // <command> '|' <job>
t_astree	*job2(t_list **toks, bool *has_error); // <command>

/*
** <job>			::= <command> '|' <job>
**					  | <command>
*/
t_astree	*job(t_list **toks, bool *has_error)
{
	t_list		*save;
	t_astree	*result;

	save = *toks;
	result = job1(toks, has_error);
	if (result != NULL || *has_error)
		return (result);
	*toks = save;
	return (job2(toks, has_error));
}

/*
** @brief <job> ::= <command> '|' <job>
*/
t_astree	*job1(t_list **toks, bool *has_error)
{
	t_astree	*cmd_node;
	t_astree	*job_node;

	cmd_node = cmd(toks, has_error);
	if (cmd_node == NULL)
		return (NULL);
	if (!move_if_is_tokentype(CHAR_PIPE, toks))
		return (astree_delete_node(cmd_node));
	job_node = job(toks, has_error);
	if (job_node == NULL)
	{
		*has_error = true;
		return (astree_delete_node(cmd_node));
	}
	return (astree_create_node(NODE_PIPE, NULL, cmd_node, job_node));
}

/*
** @brief <job> ::= <command>
*/
t_astree	*job2(t_list **toks, bool *has_error)
{
	return (cmd(toks, has_error));
}
