/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kohkubo <kohkubo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 16:06:12 by kohkubo           #+#    #+#             */
/*   Updated: 2021/08/09 16:06:13 by kohkubo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEX_H
# define LEX_H

# include "../libft/libft/libft.h"
# define PAD 256

typedef enum e_token_type
{
	CHAR_GENERAL		= -1,
	CHAR_PIPE			= '|',
	CHAR_AMPERSAND		= '&',
	CHAR_QOUTE			= '\'',
	CHAR_DQUOTE			= '\"',
	CHAR_SEMICOLON		= ';',
	CHAR_SEMICOLON2		= ';' + PAD,
	CHAR_WHITESPACE		= ' ',
	CHAR_ESCAPESEQUENCE	= '\\',
	CHAR_TAB			= '\t',
	CHAR_NEWLINE		= '\n',
	CHAR_GREATER		= '>',
	CHAR_GREATER2		= '>' + PAD,
	CHAR_LESSER			= '<',
	CHAR_LESSER2		= '<' + PAD,
	CHAR_NULL			= 0,
	TOKEN				= -1,
}	t_token_type;

typedef enum e_state_type{
	STATE_IN_DQUOTE	= '"',
	STATE_IN_QUOTE	= '\'',
	STATE_GENERAL	= -1,
	STATE_ERROR		= -2,
}	t_state_type;

/*
** Put in contents of t_list.
*/
typedef struct s_tok {
	char			*data;
	t_token_type	type;
}	t_tok;

/*
** Deliverables of lexer.
*/
typedef struct s_lexer
{
	int		len;
	t_list	*listtok;
}	t_lexer;

void	lexer_free(t_lexer **lexer);
void	tok_free(void *content);
t_tok	*tok_init(char *s);
t_lexer	*lexer_init(void);

#endif
