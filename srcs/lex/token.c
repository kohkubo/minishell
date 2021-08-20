/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kohkubo <kohkubo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 16:06:52 by kohkubo           #+#    #+#             */
/*   Updated: 2021/08/19 19:06:17 by kohkubo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"

t_token_type	token_type(char c)
{
	if (c == '|')
		return (CHAR_PIPE);
	else if (c == '\'')
		return (CHAR_QUOTE);
	else if (c == '"')
		return (CHAR_DQUOTE);
	else if (c == '>')
		return (CHAR_GREATER);
	else if (c == '<')
		return (CHAR_LESSER);
	else if (c == '\t' || c == '\v' || c == '\f' || c == '\r' || c == ' ')
		return (CHAR_SPACE);
	else if (c == 0)
		return (CHAR_NULL);
	else
		return (CHAR_GENERAL);
}

void	token_end(t_lexer *lexer, t_tok **tok, size_t n)
{
	if (n > 0)
	{
		ft_lstadd_back(&lexer->listtok, ft_lstnew(*tok));
		lexer->len++;
	}
	if (n == 0)
	{
		if ((*tok)->data[0] == 0)
			tok_free(*tok);
	}
}

void	token_end_and_create(t_lexer *lexer, t_tok **tok, char *s, size_t *n)
{
	token_end(lexer, tok, 1);
	*tok = tok_init(s);
	if (n == NULL)
		return ;
	*n = 0;
}

void	token_store_and_create(t_lexer *l, t_tok **t, char *s, t_token_type typ)
{
	t_tok	*tmp;

	tmp = *t;
	tmp->data[0] = *s;
	tmp->data[1] = 0;
	tmp->type = typ;
	token_end_and_create(l, t, s, NULL);
}

void	token_store2_and_create(t_lexer *l, t_tok **t, char **s)
{
	t_tok	*tmp;

	tmp = *t;
	tmp->data[0] = *(*s)++;
	tmp->data[1] = **s;
	tmp->data[2] = 0;
	tmp->type = **s + PAD;
	token_end_and_create(l, t, *s, NULL);
}
