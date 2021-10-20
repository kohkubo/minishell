#ifndef MINISHELL_GLOBAL_H
# define MINISHELL_GLOBAL_H

# include "libhash.h"

typedef struct s_shell
{
	t_hash_table	*env;
	int				exit_status;
	int				heredoc_status;
	char			*pwd;
}	t_shell;

extern t_shell	g_shell;

#endif
