/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kohkubo <kohkubo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 16:06:46 by kohkubo           #+#    #+#             */
/*   Updated: 2021/08/09 16:06:47 by kohkubo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lex_analyze.h"

static t_state_type	break_quote_state(\
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
		if (**s == CHAR_QOUTE)
			return (STATE_GENERAL);
	}
	return (st);
}

static t_state_type	cut_off_token(t_lexer *l, t_tok **tok, char **s, size_t *i)
{
	if (ft_isspace(**s))
		token_end_and_create(l, tok, *s, i);
	else if (**s == CHAR_PIPE || **s == CHAR_SEMICOLON)
	{
		token_end_and_create(l, tok, *s, i);
		token_store_and_create(l, tok, *s, **s);
	}
	else if (**s == 0)
		token_end(l, tok, *i);
	else if (**s == '<' || **s == '>')
	{
		if (*(*s + 1) == '<')
		{
			return (STATE_HEREDOC);
		}
		token_end_and_create(l, tok, *s, i);
		if (*(*s + 1) == '>')
			token_store2_and_create(l, tok, s);
		else
			token_store_and_create(l, tok, *s, **s);
	}
	return (STATE_GENERAL);
}

static t_state_type	generate_token(t_lexer *l, t_tok **tok, char **s, size_t *i)
{
	t_state_type	state;

	state = STATE_GENERAL;
	if (**s == '\'' || **s == '"')
	{
		state = **s;
		(*tok)->data[(*i)++] = **s;
		(*tok)->type = TOKEN;
	}
	else if (token_type(**s) == CHAR_GENERAL)
	{
		(*tok)->data[(*i)++] = **s;
		(*tok)->type = TOKEN;
	}
	else
		state = cut_off_token(l, tok, s, i);
	return (state);
}

static t_state_type	minishell_lexer_do(t_lexer *lexer, t_tok *tok, char *s)
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
			state = break_quote_state(tok, state, &s, &i);
		if (state == STATE_ERROR)
		{
			tok_free(tok);
			lexer_free(&lexer);
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
	return (minishell_lexer_do(*lexer, tok, s));
}
