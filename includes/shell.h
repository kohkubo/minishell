#ifndef SHELL_H
# define SHELL_H
# include "../libft/libft/libft.h"
# include "../libft/libex/libex.h"
# include "../libft/libhash/libhash.h"
# include <stdio.h>
# include <stdbool.h>
# define ANK 256
typedef enum e_token_type
{
	CHAR_GENERAL = -1,
	CHAR_PIPE = '|',
	CHAR_AMPERSAND = '&',
	CHAR_QOUTE = '\'',
	CHAR_DQUOTE = '\"',
	CHAR_SEMICOLON = ';',
	CHAR_WHITESPACE = ' ',
	CHAR_ESCAPESEQUENCE = '\\',
	CHAR_TAB = '\t',
	CHAR_NEWLINE = '\n',
	CHAR_GREATER = '>',
	CHAR_GREATER2 = '>' + ANK,
	CHAR_LESSER = '<',
	CHAR_LESSER2 = '<' + ANK,
	CHAR_NULL = 0,
	TOKEN	= -1,
}	t_token_type;
typedef enum e_state{
	STATE_IN_DQUOTE = '"',
	STATE_IN_QUOTE = '\'',
	STATE_GENERAL = -1,
}	t_state;
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

void			parse(char *input);
int				ft_exit(char **arg);
int				ft_echo(char **args);
void			display_lexer(void *content);
void			test(char *s);

#endif
