#include "exec.h"

#include <errno.h>
#include "shell.h"
#include "astree.h"
#include "libft.h"
#include "libex.h"

int	access_error_handle(char *msg)
{
	if (errno == ENOENT)
	{
		if (!ft_strchr(msg, '/'))
			return (command_not_found(msg));
		return (minishell_perror(msg, 127));
	}
	else if (errno == EACCES)
		return (minishell_perror(msg, 126));
	else
		return (minishell_perror(msg, 1));
}

int	exec_with_path(char *cmd, char **args, char **envp)
{
	const char	*path_str;
	char		**fullpaths;
	int			i;
	int			res;

	path_str = hash_getstr(g_shell.env, "PATH");
	fullpaths = get_fullpath(path_str, cmd);
	if (fullpaths == NULL)
	{
		errno = ENOENT;
		return (minishell_perror(cmd, 127));
	}
	res = -1;
	i = 0;
	while (fullpaths && fullpaths[i])
	{
		if (access(fullpaths[i], X_OK) == 0)
			res = catch_error(execve(fullpaths[i], args, envp), cmd);
		i++;
	}
	if (res < 0)
		res = access_error_handle(cmd);
	if (fullpaths)
		free_string_array(fullpaths);
	return (res);
}

char	**tree_to_argv(t_astree *tree)
{
	t_astree	*tmp;
	size_t		len;
	char		**ret;

	tmp = tree;
	len = 0;
	while (tmp)
	{
		tmp = tmp->right;
		len++;
	}
	ret = (char **)ft_xmalloc(sizeof(char *) * (len + 1));
	len = 0;
	while (tree)
	{
		ret[len] = minishell_expand(tree->data, expand_handler);
		tree = tree->right;
		len++;
	}
	ret[len] = NULL;
	return (ret);
}

/**
 * <simple command>::= <pathname> <token list>
 */
int	execute_simplecmd(t_astree *tree)
{
	char	**args;
	char	**envp;
	int		res;

	errno = 0;
	args = tree_to_argv(tree);
	if (is_builtin(tree))
		res = exec_builtin(tree->data, args);
	else
	{
		envp = hash_getall(g_shell.env, NULL);
		if (!ft_strchr(tree->data, '/'))
			res = exec_with_path(tree->data, args, envp);
		else if (access(tree->data, X_OK) == 0)
			res = catch_error(execve(tree->data, args, envp), tree->data);
		else
			res = access_error_handle(tree->data);
		free_string_array(envp);
	}
	if (args)
		args = free_string_array(args);
	return (res);
}
