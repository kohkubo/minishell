#include "shell.h"
#include "parse.h"

bool	move_if_is_tokentype(t_token_type type, t_list **current)
{
	if (*current == NULL)
		return (false);
	if (((t_tok *)(*current)->content)->type == type)
	{
		*current = (*current)->next;
		return (true);
	}
	return (false);
}

bool	allocate_data_if_is_token(t_list **current, char **buf_ptr)
{
	if (*current == NULL)
		return (false);
	if (((t_tok *)(*current)->content)->type == TOKEN)
	{
		*buf_ptr = ft_xstrdup(((t_tok *)(*current)->content)->data);
		*current = (*current)->next;
		return (true);
	}
	return (false);
}

/**
<command line>		::= <job> ';' <command line>	// not make
					  | <job> ';'					// not make
					  | <job> '&' <command line>	// not make
					  | <job> '&'					// not make
					  | <job>

<job>				::= <command> '|' <job>
					  | <command>

<command>			::= <token list> <command>
					  | <redirection list> <command>
					  | (EMPTY)

<redirection list>	::= <redirection> <redirection list>

<redirection>		::= '<' <filename>
					  | '>' <filename>
					  | '<<' <filename>
					  | '>>' <filename>

<token list>		::= <token> <token list>
					  | (EMPTY)
*/
bool	parse(t_lexer *lex, t_astree **res_buf)
{
	t_list	*tokens;
	bool	has_error;

	if (res_buf == NULL)
		return (false);
	has_error = false;
	tokens = lex->listtok;
	*res_buf = cmdline(&tokens, &has_error);
	if (tokens != NULL || has_error)
	{
		g_shell.exit_status = 258;
		ft_putstr_fd("syntax error near unexpected token `", 2);
		if (tokens == NULL)
			ft_putstr_fd("newline", 2);
		else
			ft_putstr_fd(((t_tok *)tokens->content)->data, 2);
		ft_putendl_fd("'", 2);
		return (false);
	}
	return (true);
}
