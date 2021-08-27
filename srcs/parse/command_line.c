#include "parse.h"
t_astree	*cmdline1(t_list **toks); // <job> ';' <command line>
t_astree	*cmdline2(t_list **toks); // <job> ';'
t_astree	*cmdline3(t_list **toks); // <job>

/*
** <command line>	::= <job> ';' <command line>
**					  | <job> ';'
**					  | <job> '&' <command line>	// not make
**					  | <job> '&'					// not make
**					  | <job>
*/
t_astree	*cmdline(t_list **toks)
{
	t_list		*save;
	t_astree	*result;

	save = *toks;
	result = cmdline1(toks);
	if (result != NULL)
		return (result);
	*toks = save;
	result = cmdline2(toks);
	if (result != NULL)
		return (result);
	*toks = save;
	return (cmdline3(toks));
}

/*
** @brief <command line> ::= <job> ';' <command line>
*/
t_astree	*cmdline1(t_list **toks)
{
	t_astree	*job_node;
	t_astree	*cmdline_node;

	job_node = job(toks);
	if (job_node == NULL)
		return (NULL);
	if (!move_if_is_tokentype(CHAR_SEMICOLON, toks))
		return (astree_delete_node(job_node));
	cmdline_node = cmdline(toks);
	if (cmdline_node == NULL)
		return (astree_delete_node(job_node));
	return (astree_create_node(NODE_SEQ, NULL, job_node, cmdline_node));
}

/*
** @brief <command line> ::= <job> ';'
*/
t_astree	*cmdline2(t_list **toks)
{
	t_astree	*job_node;
	t_astree	*result;

	job_node = job(toks);
	if (job_node == NULL)
		return (NULL);
	if (!move_if_is_tokentype(CHAR_SEMICOLON, toks))
		return (astree_delete_node(job_node));
	return (astree_create_node(NODE_SEQ, NULL, job_node, NULL));
}

/*
** @brief <command line> ::= <job>
*/
t_astree	*cmdline3(t_list **toks)
{
	return (job(toks));
}
