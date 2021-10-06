#include "exec.h"

#include "shell.h"
#include "astree.h"
#include "libft.h"
#include "error.h"

char	**get_fullpath(const char *path, char *cmd)
{
	char	**paths;
	int		i;

	if (path == NULL || cmd == NULL)
		return (NULL);
	paths = catch_nul(ft_split(path, ':'), "split");
	i = 0;
	while (paths[i])
	{
		if (paths[i][ft_strlen(paths[i]) - 1] != '/')
			free_set((void **)&paths[i],
				catch_nul(ft_strjoin(paths[i], "/"), "ft_strjoin"));
		free_set((void **)&paths[i],
			catch_nul(ft_strjoin(paths[i], cmd), "ft_strjoin"));
		i++;
	}
	return (paths);
}

int	exec_with_path(char *cmd, char **args, char **envp)
{
	char	**fullpaths;
	int		i;
	int		res;

	fullpaths = get_fullpath(hash_getstr(g_shell.env, "PATH"), cmd);
	res = -1;
	i = 0;
	while (fullpaths && fullpaths[i])
	{
		if (access(fullpaths[i], X_OK) == 0)
			res = catch_err(execve(fullpaths[i], args, envp), cmd);
		i++;
	}
	if (res < 0 && errno == ENOENT)
		res = command_not_found(cmd);
	else if (res < 0 && errno == EACCES)
		res = minishell_perror(cmd, 126);
	else if (res < 0)
		res = minishell_perror(cmd, 1);
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
		ret[len] = minishell_expand(tree->data);
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

	args = tree_to_argv(tree);
	if (is_builtin(tree))
		res = exec_builtin(tree->data, args);
	else
	{
		envp = hash_getall(g_shell.env, NULL);
		if (!ft_strchr(tree->data, '/'))
			res = exec_with_path(tree->data, args, envp);
		else if (access(tree->data, X_OK) == 0)
			res = catch_err(execve(tree->data, args, envp), tree->data);
		else if (errno == ENOENT)
			res = minishell_perror(tree->data, 127);
		else if (errno == EACCES)
			res = minishell_perror(tree->data, 126);
		else
			res = minishell_perror(tree->data, 1);
		free_string_array(envp);
	}
	if (args)
		args = free_string_array(args);
	return (res);
}
