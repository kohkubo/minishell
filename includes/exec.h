#ifndef EXEC_H
# define EXEC_H

# include <stdbool.h>
# include <sys/types.h>
# include "astree.h"

void	execute_cmdline(t_astree *tree, int *status);
void	execute_job(t_astree *tree, int *status, pid_t *pid);
int		execute_cmd(t_astree *tree);
void	execute_redirection(t_astree *tree);
int		execute_simplecmd(t_astree *tree);
int		exec_builtin(char *cmd, char **args);
bool	is_builtin(t_astree *tree);
int		command_not_found(char *cmd);
int		minishell_perror(char *cmd, int status);

void	connect_pipe(int pipefd[2], int fd);

#endif
