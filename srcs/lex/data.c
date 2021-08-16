/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kohkubo <kohkubo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 16:06:41 by kohkubo           #+#    #+#             */
/*   Updated: 2021/08/09 16:06:41 by kohkubo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"

t_tok	*tok_init(char *s)
{
	size_t	len;
	t_tok	*tok;

	tok = ft_xcalloc(sizeof(t_tok), 1);
	len = ft_strlen(s) + 1;
	tok->data = ft_xcalloc(len, 1);
	return (tok);
}

t_lexer	*lexer_init(void)
{
	t_lexer	*lexer;

	lexer = ft_xcalloc(sizeof(t_lexer), 1);
	return (lexer);
}

void	tok_free(void *content)
{
	t_tok	*tok;

	tok = (t_tok *)content;
	free(tok->data);
	tok->data = NULL;
	free(tok);
}

void	lexer_free(t_lexer **lexer)
{
	ft_lstclear(&(*lexer)->listtok, tok_free);
	free(*lexer);
	*lexer = NULL;
}
