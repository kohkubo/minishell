#include "lex.h"
#include "shell.h"

static t_state_type	store_char_and_check_state(\
t_tok *tok, t_state_type st, char **s, size_t *i)
{
	if (st == STATE_IN_DQUOTE)
	{
		tok->data[(*i)++] = **s;
		if (**s == CHAR_DQUOTE)
			return (STATE_GENERAL);
	}
	else if (st == STATE_IN_QUOTE)
	{
		tok->data[(*i)++] = **s;
		if (**s == CHAR_QUOTE)
			return (STATE_GENERAL);
	}
	return (st);
}

static t_state_type	cut_off_token(t_lexer *l, t_tok **tok, char **s, size_t *i)
{
	if (ft_isspace(**s))
		token_end_and_create(l, tok, *s, i);
	else if (**s == CHAR_NULL)
		token_end(l, tok, *i);
	else if (ft_strncmp(*s, ">>", 2) == 0)
	{
		token_end_and_create(l, tok, *s, i);
		token_store2_and_create(l, tok, s);
	}
	else if (**s == CHAR_GREATER || **s == CHAR_LESSER || **s == CHAR_PIPE)
	{
		token_end_and_create(l, tok, *s, i);
		token_store_and_create(l, tok, *s, **s);
	}
	return (STATE_GENERAL);
}

static t_state_type	generate_token(\
t_lexer **l, t_tok **tok, char **s, size_t *i)
{
	t_state_type	state;

	state = STATE_GENERAL;
	if (**s == '\'' || **s == '"')
	{
		if (**s == '\'')
			state = STATE_IN_QUOTE;
		else
			state = STATE_IN_DQUOTE;
		(*tok)->data[(*i)++] = **s;
		(*tok)->type = TOKEN;
		return (state);
	}
	else if (ft_strncmp(*s, "<<", 2) == 0)
		state = heredoc(l, tok, s, i);
	if (state == STATE_ERROR)
		return (state);
	else if (token_type(**s) == CHAR_GENERAL)
	{
		(*tok)->data[(*i)++] = **s;
		(*tok)->type = TOKEN;
	}
	else
		state = cut_off_token(*l, tok, s, i);
	return (state);
}

static t_state_type	minishell_lexer_do(t_lexer **lexer, t_tok *tok, char *s)
{
	t_state_type	state;
	size_t			i;

	i = 0;
	state = STATE_GENERAL;
	while (1)
	{
		if (state == STATE_GENERAL)
			state = generate_token(lexer, &tok, &s, &i);
		else
			state = store_char_and_check_state(tok, state, &s, &i);
		if (*s == 0 && state != STATE_ERROR && state != STATE_GENERAL)
		{
			tok_free(tok);
			lexer_free(lexer);
			ft_error_exit("this pattern is not supported");
			return (state);
		}
		if (*s == 0)
			break ;
		s++;
	}
	return (state);
}

t_state_type	minishell_lexer(char *s, t_lexer **lexer)
{
	t_tok	*tok;

	if (s == NULL)
		ft_fatal("minishell_lexer : Invalid argument");
	*lexer = lexer_init();
	tok = tok_init(s);
	return (minishell_lexer_do(lexer, tok, s));
}
