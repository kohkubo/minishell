#include "shell.h"

#include "libft.h"
#include "libex.h"

char	*dup_a_path(const char *path, int start, int end)
{
	char	*data;

	if (end - start == 0)
		data = ft_xstrdup(".");
	else
		data = ft_xsubstr(path, start, end - start);
	return (data);
}

t_list	*split_path(const char *path)
{
	t_list	*list;
	size_t	i;
	size_t	start;

	list = NULL;
	i = 0;
	start = 0;
	while (path[i])
	{
		if (path[i] == ':')
		{
			ft_lstadd_back(&list, ft_xlstnew(dup_a_path(path, start, i)));
			start = i + 1;
		}
		i++;
	}
	ft_lstadd_back(&list, ft_xlstnew(dup_a_path(path, start, i)));
	return (list);
}

char	**get_fullpath(const char *path, char *cmd)
{
	t_list	*paths;
	t_list	*save;
	char	*data;
	char	**ret;

	if (path == NULL || cmd == NULL || ft_strlen(path) == 0)
		return (NULL);
	paths = split_path(path);
	save = paths;
	while (paths)
	{
		data = paths->content;
		if (data[ft_strlen(data) - 1] != '/')
			free_set(&data, ft_xstrjoin(data, "/"));
		free_set(&data, ft_xstrjoin(data, cmd));
		paths->content = data;
		paths = paths->next;
	}
	ret = lst_to_array(save);
	ft_lstclear(&save, free);
	return (ret);
}
