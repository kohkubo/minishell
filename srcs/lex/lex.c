#include "../../includes/lex.h"

bool	minishell_lexer3(t_tok **tok, t_state_type *state, char **s, size_t *i)
{
	if (**s == '\'')
	{
		*state = STATE_IN_QUOTE;
		(*tok)->data[(*i)++] = **s;
		(*tok)->type = TOKEN;
	}
	else if (**s == '"')
	{
		*state = STATE_IN_DQUOTE;
		(*tok)->data[(*i)++] = **s;
		(*tok)->type = TOKEN;
	}
	else if (**s == '\\')
	{
		(*tok)->data[(*i)++] = *(++*s);
		(*tok)->type = TOKEN;
	}
	else if (token_type(**s) == CHAR_GENERAL)
	{
		(*tok)->data[(*i)++] = **s;
		(*tok)->type = TOKEN;
	}
	else
		return (false);
	return (true);
}

void	cut_off_token(t_lexer *lexer, t_tok **tok, char **s, size_t *i)
{
	if (ft_isspace(**s))
		token_end_and_create(lexer, tok, *s, i);
	else if (**s == CHAR_PIPE || **s == CHAR_SEMICOLON)
	{
		token_end_and_create(lexer, tok, *s, i);
		token_store_and_create(lexer, tok, *s, **s);
	}
	else if (**s == 0)
		token_end(lexer, tok, *i);
	else if (ft_strchr("<>", **s))
	{
		token_end_and_create(lexer, tok, *s, i);
		if (ft_strchr("<>", *(*s + 1)))
		{
			(*tok)->data[0] = *(*s)++;
			(*tok)->data[1] = **s;
			(*tok)->type = **s + PAD;
			token_end_and_create(lexer, tok, *s, NULL);
		}
		else
			token_store_and_create(lexer, tok, *s, **s);
	}
}

void	break_quote_state(t_tok *tok, t_state_type *state, char *s, size_t *i)
{
	if (*state == STATE_IN_DQUOTE)
	{
		tok->data[(*i)++] = *s;
		if (*s == CHAR_DQUOTE)
			*state = STATE_GENERAL;
	}
	else if (*state == STATE_IN_QUOTE)
	{
		tok->data[(*i)++] = *s;
		if (*s == CHAR_QOUTE)
			*state = STATE_GENERAL;
	}
}

void	minishell_lexer2(t_lexer *lexer, t_tok *tok, char *s)
{
	t_state_type	state;
	size_t			i;

	i = 0;
	state = STATE_GENERAL;
	while (1)
	{
		if (state == STATE_GENERAL)
		{
			if (!minishell_lexer3(&tok, &state, &s, &i))
				cut_off_token(lexer, &tok, &s, &i);
		}
		else
		{
			break_quote_state(tok, &state, s, &i);
		}
		if (*s == 0)
			break ;
		s++;
	}
}

t_lexer	*minishell_lexer(char *s)
{
	t_lexer			*lexer;
	t_tok			*tok;
	t_state_type	state;
	size_t			i;

	if (s == NULL)
		ft_fatal("minishell_lexer : Invalid argument");
	lexer = lexer_init();
	tok = tok_init(s);
	i = 0;
	state = STATE_GENERAL;
	while (1)
	{
		if (state == STATE_GENERAL)
		{
			if (!minishell_lexer3(&tok, &state, &s, &i))
				cut_off_token(lexer, &tok, &s, &i);
		}
		else
			break_quote_state(tok, &state, s, &i);
		if (*s == 0)
			break ;
		s++;
	}
	return (lexer);
}
