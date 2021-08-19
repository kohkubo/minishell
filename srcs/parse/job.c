#include "parse.h"

t_astree	*job1(t_list **toks); // <command> '|' <job>
t_astree	*job2(t_list **toks); // <command>

/*
** <job>			::= <command> '|' <job>
**					  | <command>
*/
t_astree	*job(t_list **toks)
{
	t_list		*save;
	t_astree	*result;

	save = *toks;
	result = job1(toks);
	if (result != NULL)
		return (result);
	*toks = save;
	return (job2(toks));
}

/*
** @brief <job> ::= <command> '|' <job>
*/
t_astree	*job1(t_list **toks)
{
	t_astree	*cmd_node;
	t_astree	*job_node;

	cmd_node = cmd(toks);
	if (cmd_node == NULL)
		return (NULL);
	if (!is_tokentype_and_store_data(CHAR_PIPE, toks, NULL))
		return (astree_delete_node(cmd_node));
	job_node = job(toks);
	if (job_node == NULL)
		return (astree_delete_node(cmd_node));
	return (astree_create_node(NODE_PIPE, NULL, cmd_node, job_node));
}

/*
** @brief <job> ::= <command>
*/
t_astree	*job2(t_list **toks)
{
	return (cmd(toks));
}
