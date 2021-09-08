#include "exec.h"

#include <sys/wait.h>
#include <unistd.h>
#include "shell.h"
#include "astree.h"
#include "libft.h"
#include "libex.h"

#define CHILD (0)

char	**get_fullpath(const char *path, char *cmd)
{
	char	**paths;
	int		i;

	if (path == NULL || cmd == NULL)
		return (NULL);
	paths = catch_null(ft_split(path, ':'), "split");
	i = 0;
	while (paths[i])
	{
		if (paths[i][ft_strlen(paths[i]) - 1] != '/')
			free_set((void **)&paths[i],
				catch_null(ft_strjoin(paths[i], "/"), "ft_strjoin"));
		free_set((void **)&paths[i],
			catch_null(ft_strjoin(paths[i], cmd), "ft_strjoin"));
		i++;
	}
	return (paths);
}

void	exec_with_path(char *cmd, char **args, char **envp)
{
	char	**fullpaths;
	int		i;

	fullpaths = get_fullpath(hash_getstr(g_shell.env, "PATH"), cmd);
	i = 0;
	while (fullpaths && fullpaths[i])
	{
		if (access(fullpaths[i], X_OK) == 0)
			exit(catch_error(execve(fullpaths[i], args, envp), cmd));
		i++;
	}
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putendl_fd(": command not found", 2);
	exit(1);
}

typedef int			(*t_builtIn_func)(char **arg);

/**
 * @return true if builtin was run, false otherwise.
 */
bool	run_if_builtin(char *cmd, char **args, int *status)
{
	char			**builtIn_names;
	t_builtIn_func	*builtIn_funcs;
	int				i;

	builtIn_names = (char *[]){
		"echo", "cd", "pwd", "export", "unset", "env", "exit", NULL};
	i = contain(builtIn_names, cmd);
	if (i < 0)
		return (false);
	builtIn_funcs = (t_builtIn_func []){
		ft_echo, NULL, ft_pwd, ft_export, ft_unset, ft_env, ft_exit, NULL};
	if (builtIn_funcs[i] != NULL)
		*status = builtIn_funcs[i](&args[1]);
	else
	{
		ft_putstr_fd(cmd, 2);
		ft_putendl_fd(" is not implemented yet", 2);
		exit(1);
	}
	return (true);
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
void	execute_simplecmd(t_astree *tree, int *status)
{
	char	**args;
	char	**envp;
	pid_t	pid;

	args = tree_to_argv(tree);
	if (run_if_builtin(tree->data, args, status) == false)
	{
		pid = catch_error(fork(), "fork");
		if (pid == CHILD)
		{
			envp = hash_getall(g_shell.env, NULL);
			if (!ft_strchr(tree->data, '/'))
				exec_with_path(tree->data, args, envp);
			else
				exit(catch_error(execve(tree->data, args, envp), tree->data));
		}
		catch_error(waitpid(pid, status, 0), "waitpid");
	}
	if (args)
		args = free_string_array(args);
}
