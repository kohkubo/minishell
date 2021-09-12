#include "parse.h"
t_astree	*cmdline1(t_list **toks, bool *has_error); // <job>';'<command line>
t_astree	*cmdline2(t_list **toks, bool *has_error); // <job> ';'
t_astree	*cmdline3(t_list **toks, bool *has_error); // <job>

/*
** <command line>	::= <job> ';' <command line>	// not make
**					  | <job> ';'					// not make
**					  | <job> '&' <command line>	// not make
**					  | <job> '&'					// not make
**					  | <job>
*/
t_astree	*cmdline(t_list **toks, bool *has_error)
{
	return (cmdline3(toks, has_error));
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
** <command line> ::= <job>
*/
t_astree	*cmdline3(t_list **toks, bool *has_error)
{
	return (job(toks, has_error));
}
