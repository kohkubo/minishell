#ifndef LEX_H
# define LEX_H

# include "libft.h"
# include "libex.h"
# define PAD 256

typedef enum e_token_type
{
	CHAR_GENERAL		= -1,
	CHAR_SPACE			= ' ',
	CHAR_PIPE			= '|',
	CHAR_PIPE2			= '|' + PAD,
	CHAR_AMPERSAND		= '&',
	CHAR_AMPERSAND2		= '&' + PAD,
	CHAR_SQUOTE			= '\'',
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
	CHAR_DOL			= '$',
	CHAR_ENV			= '$' + PAD,
	CHAR_NULL			= 0,
	TOKEN				= -1,
}	t_token_type;

typedef enum e_state_type{
	STATE_IN_DQUOTE		= '"',
	STATE_IN_SQUOTE		= '\'',
	STATE_IN_HEREDOC	= '<' + PAD,
	STATE_GENERAL		= -1,
	STATE_ERROR			= -2,
}	t_state_type;

# define GREATER2 ">>"
# define LESSER2 "<<"
# define QUOTES "\'\""
# define SEPARATOR "\t\n\v\f\r <>|"
# define TOKEN_WSPACE "\t\n\v\f\r "
# define TOKEN_WSPACE_QUOTES "\t\n\v\f\r \'\""

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

t_tok			*tok_new(char *s, t_token_type type);
t_lexer			*lexer_new(t_list *listtok);
void			tok_free(void *content);
void			lexer_free(t_lexer **lexer);
char			*heredoc_readline(char *heredoc);
t_state_type	store_quote_token(t_list **lst, char **token, t_list **ret);
void			store_general_token(t_list **lst, char **token, t_list **ret);
t_state_type	store_heredoc_token(t_list **lst, char **token, t_list **ret);

#endif
