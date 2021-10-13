#include "shell.h"

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
