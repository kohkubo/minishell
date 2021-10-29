#include "shell.h"

static bool	ft_cd_do(char *path, char *oldpwd, bool printflg)
{
	if (chdir(path) == -1)
		return (false);
	path = getcwd(NULL, 0);
	if (path == NULL)
	{
		ft_putstr_fd("cd: error retrieving current directory: \
		getcwd: cannot access parent directories: \
		No such file or directory\n", 2);
		path = ft_xstrjoin(oldpwd, "/.");
	}
	if (printflg)
		printf("%s\n", path);
	hash_setstr(g_shell.env, "PWD", path);
	hash_setstr(g_shell.env, "OLDPWD", oldpwd);
	free_set((void **) &g_shell.pwd, path);
	free_set((void **) &oldpwd, NULL);
	return (true);
}

static int	ft_cd_no_such_fild_or_dir(char *path, char *oldpwd)
{
	ft_putstr_fd("cd: no such file or directory: ", 2);
	ft_putendl_fd(path, 2);
	hash_setstr(g_shell.env, "OLDPWD", oldpwd);
	free_set((void **) &oldpwd, NULL);
	return (1);
}

static int	ft_cd_cdpath(char *path, char *oldpwd, const char *cdpath)
{
	bool	flg;
	char	**paths;
	int		i;

	flg = false;
	if (!ft_cd_do(path, oldpwd, false))
	{
		paths = get_fullpath(cdpath, path);
		i = 0;
		while (paths[i])
		{
			if (ft_cd_do(paths[i], oldpwd, true))
			{
				flg = true;
				break ;
			}
			i++;
		}
		free_string_array(paths);
		if (flg == false)
			return (ft_cd_no_such_fild_or_dir(path, oldpwd));
	}
	return (0);
}

int	ft_cd(char **args)
{
	char		*path;
	char		*oldpwd;
	const char	*cdpath;

	if (args[0] == NULL)
	{
		path = getenv("HOME");
		if (path == NULL)
		{
			ft_putstr_fd("cd: HOME not set\n", 2);
			return (1);
		}
	}
	else
		path = args[0];
	oldpwd = ft_xstrdup((char *)hash_getstr(g_shell.env, "PWD"));
	cdpath = hash_getstr(g_shell.env, "CDPATH");
	if (cdpath != NULL && path[0] != '/')
		return (ft_cd_cdpath(path, oldpwd, cdpath));
	else
		if (!ft_cd_do(path, oldpwd, false))
			return (ft_cd_no_such_fild_or_dir(path, oldpwd));
	return (0);
}
