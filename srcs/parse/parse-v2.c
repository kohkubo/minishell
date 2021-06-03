#include "shell.h"
#include "parse.h"

bool	is_tokentype(t_token_type type, t_list **current)
{
	if (((t_tok *)(*current)->content)->type == type)
	{
		*current = (*current)->next;
		return (true);
	}
	return (false);
}

bool	parse_v2(t_lexer *lex, t_astree **res_buf)
{
	if (lex == NULL || lex->len == 0 || res_buf == NULL)
		return (false);
	*res_buf = cmdline(&lex->listtok);
	if (lex->listtok != NULL
		&& ((t_tok *)lex->listtok->content)->type != CHAR_NULL)
	{
		ft_putstr_fd("Syntax Error near unexpected token `", 2);
		ft_putstr_fd(((t_tok *)lex->listtok->content)->data, 2);
		ft_putendl_fd("'", 2);
		return (false);
	}
	return (true);
}
