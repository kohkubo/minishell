#include "parse.h"
t_astree	*cmdline1(t_list **toks, bool *has_error); // <job>';'<command line>
t_astree	*cmdline2(t_list **toks, bool *has_error); // <job> ';'
// <job> '&&' <command line>
t_astree	*cmdline_job_and_cmdline(t_list **toks, bool *has_error);
// <job> '||' <command line>
t_astree	*cmdline_job_or_cmdline(t_list **toks, bool *has_error);

/*
** <command line>	::= <job> ';' <command line>	// not make
**					  | <job> ';'					// not make
**					  | <job> '&' <command line>	// not make
**					  | <job> '&'					// not make
**					  | <job> '&&' <command line>
**					  | <job> '||' <command line>
**					  | <job>
*/
t_astree	*cmdline(t_list **toks, bool *has_error)
{
	t_list		*save;
	t_astree	*result;

	save = *toks;
	result = cmdline_job_and_cmdline(toks, has_error);
	if (result != NULL || *has_error)
		return (result);
	*toks = save;
	result = cmdline_job_or_cmdline(toks, has_error);
	if (result != NULL || *has_error)
		return (result);
	*toks = save;
	return (job(toks, has_error));
}

/*
** <command line> ::= <job> ';' <command line>
*/
t_astree	*cmdline1(t_list **toks, bool *has_error)
{
	t_astree	*job_node;
	t_astree	*cmdline_node;

	job_node = job(toks, has_error);
	if (job_node == NULL)
		return (NULL);
	if (!move_if_is_tokentype(CHAR_SEMICOLON, toks))
		return (astree_delete_node(job_node));
	cmdline_node = cmdline(toks, has_error);
	if (cmdline_node == NULL)
		return (astree_delete_node(job_node));
	return (astree_create_node(NODE_SEQ, NULL, job_node, cmdline_node));
}

/*
** <command line> ::= <job> ';'
*/
t_astree	*cmdline2(t_list **toks, bool *has_error)
{
	t_astree	*job_node;

	job_node = job(toks, has_error);
	if (job_node == NULL)
		return (NULL);
	if (!move_if_is_tokentype(CHAR_SEMICOLON, toks))
		return (astree_delete_node(job_node));
	return (astree_create_node(NODE_SEQ, NULL, job_node, NULL));
}

/*
** <job> '&&' <command line>
*/
t_astree	*cmdline_job_and_cmdline(t_list **toks, bool *has_error)
{
	t_astree	*job_node;
	t_astree	*cmdline_node;

	job_node = job(toks, has_error);
	if (job_node == NULL)
		return (NULL);
	if (!move_if_is_tokentype(CHAR_AMPERSAND2, toks))
		return (astree_delete_node(job_node));
	cmdline_node = cmdline(toks, has_error);
	if (cmdline_node == NULL)
		return (astree_delete_node(job_node));
	return (astree_create_node(NODE_AND, NULL, job_node, cmdline_node));
}

/*
** <job> '||' <command line>
*/
t_astree	*cmdline_job_or_cmdline(t_list **toks, bool *has_error)
{
	t_astree	*job_node;
	t_astree	*cmdline_node;

	job_node = job(toks, has_error);
	if (job_node == NULL)
		return (NULL);
	if (!move_if_is_tokentype(CHAR_PIPE2, toks))
		return (astree_delete_node(job_node));
	cmdline_node = cmdline(toks, has_error);
	if (cmdline_node == NULL)
		return (astree_delete_node(job_node));
	return (astree_create_node(NODE_OR, NULL, job_node, cmdline_node));
}
