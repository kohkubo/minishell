#ifndef SHELL_H
# define SHELL_H
# include "libft.h"
# include "libex.h"
# include "libhash.h"
# define PROMPT "minishell> "
# define QUOTE_PROMPT "quote... "
# define DQUOTE_PROMPT "dquote... "
# define HEREDOC_PROMPT "heredoc... "
# include "lex.h"
# include "astree.h"
# include <stdio.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_shell
{
	t_hash_table	*env;
	int				exit_status;
	char			*pwd;
}	t_shell;

extern t_shell	g_shell;

t_state_type	minishell_lexer(char *s, t_lexer **lexer);
void			parse(char *input);
int				ft_exit(char **arg);
int				ft_echo(char **args);
void			minishell_init(void);
void			store_shellenv(char **arr, t_hash_table *table);
int				ft_env(char **args);
int				ft_export(char **args);
int				ft_unset(char **args);
int				ft_pwd(char **args);
int				ft_cd(char **args);
bool			parse_v2(t_lexer *lex, t_astree **res_buf);
int				minishell_execute(t_astree *tree);
char			*minishell_expand(char *arg, void (*handler)(t_list *));
void			expand_handler(t_list *lst);
void			expand_handler_heredoc(t_list *lst);
char			**get_fullpath(const char *path, char *cmd);

#endif
