#ifndef EXEC_H
# define EXEC_H

# include "astree.h"

void	execute_cmdline(t_astree *tree, int *status);
void	execute_job(t_astree *tree, int *status);
void	execute_cmd(t_astree *tree, int *status);
void	execute_simplecmd(t_astree *tree, int *status);

#endif
