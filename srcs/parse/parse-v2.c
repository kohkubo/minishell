#include "shell.h"
#include "parse.h"
#include "logging.h"

bool	is_tokentype(t_token_type type, t_list **current, char **buf_ptr)
{
	if (*current == NULL)
		return (false);
	if (((t_tok *)(*current)->content)->type == type)
	{
		if (buf_ptr != NULL)
			*buf_ptr = ft_xstrdup(((t_tok *)(*current)->content)->data);
		*current = (*current)->next;
		return (true);
	}
	return (false);
}

/**
<command line>		::= <job> ';' <command line>
					  | <job> ';'
					  | <job> '&' <command line>	// not make
					  | <job> '&'					// not make
					  | <job>

<job>				::= <command> '|' <job>
					  | <command>

<command>			::= <simple command> <redirection list>
					  | <simple command>

<redirection list>	::= <redirection> <redirection list>

<redirection>		::= '<' <filename> <token list>
					  | '>' <filename> <token list>
					  | '<<' <filename> <token list>
					  | '>>' <filename> <token list>
// <token list> will be added after the arg of the previous <simple command>.

<simple command>	::= <pathname> <token list>

<token list>		::= <token> <token list>
					  | (EMPTY)
*/
bool	parse_v2(t_lexer *lex, t_astree **res_buf)
{
	t_list *tokens;

	if (lex == NULL || lex->len == 0 || res_buf == NULL)
		return (false);
	tokens = lex->listtok;
	*res_buf = cmdline(&tokens);
	if (tokens != NULL && ((t_tok *)tokens->content)->type != CHAR_NULL)
	{
		ft_putstr_fd("Syntax Error near unexpected token `", 2);
		ft_putstr_fd(((t_tok *)tokens->content)->data, 2);
		ft_putendl_fd("'", 2);
		return (false);
	}
	return (true);
}
