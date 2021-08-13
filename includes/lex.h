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
	CHAR_QUOTE			= '\'',
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
	STATE_IN_DQUOTE		= '"',
	STATE_IN_QUOTE		= '\'',
	STATE_IN_HEREDOC	= '<' + PAD,
	STATE_GENERAL		= -1,
	STATE_ERROR			= -2,
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

char			*shell_prompt(t_state_type state);
t_token_type	token_type(char c);
void			token_end(t_lexer *lexer, t_tok **tok, size_t n);
void			token_end_and_create(\
t_lexer *lexer, t_tok **tok, char *s, size_t *n);
void			token_store_and_create(\
t_lexer *l, t_tok **t, char *s, t_token_type typ);
void			token_store2_and_create(t_lexer *l, t_tok **t, char **s);
char			*heredoc_readline(char *heredoc, char *tok);
char			*generate_heredoc(char *s);
t_tok			*tok_init(char *s);
t_lexer			*lexer_init(void);
void			tok_free(void *content);
void			lexer_free(t_lexer **lexer);
t_state_type	heredoc(t_lexer **l, t_tok **tok, char **s, size_t *i);

#endif
