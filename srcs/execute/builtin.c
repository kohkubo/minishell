#include "exec.h"

#include <stdbool.h>
#include "shell.h"
#include "astree.h"

typedef int	(*t_builtIn_func)(char **arg);

bool	is_builtin(t_astree *tree)
{
	char			**builtIn_names;

	if (tree->type & NODE_REDIRECTION)
		tree = tree->left;
	if (!(tree->type & NODE_CMDPATH))
		return (false);
	builtIn_names = (char *[]){
		"echo", "cd", "pwd", "export", "unset", "env", "exit", NULL};
	if (contain(builtIn_names, tree->data) < 0)
		return (false);
	return (true);
}

/**
 * @return true if builtin was run, false otherwise.
 */
int	exec_builtin(char *cmd, char **args)
{
	char			**builtIn_names;
	t_builtIn_func	*builtIn_funcs;
	int				i;

	builtIn_names = (char *[]){
		"echo", "cd", "pwd", "export", "unset", "env", "exit", NULL};
	i = contain(builtIn_names, cmd);
	if (i < 0)
		return (command_not_found(cmd));
	builtIn_funcs = (t_builtIn_func []){
		ft_echo, ft_cd, ft_pwd, ft_export, ft_unset, ft_env, ft_exit, NULL};
	if (builtIn_funcs[i] != NULL)
		return (builtIn_funcs[i](&args[1]));
	else
		return (command_not_found(cmd));
}
