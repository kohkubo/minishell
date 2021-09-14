#include "libex.h"

t_list	*separate_to_list(char *str, char *separator)
{
	t_list	*list;
	char	*buf;
	int		i;

	list = NULL;
	buf = ft_xmalloc(sizeof(char) * (ft_strlen(str) + 1));
	while (*str != '\0')
	{
		if (ft_strchr(separator, *str) != NULL)
		{
			ft_lstadd_back(&list, ft_lstnew(ft_xsubstr(str, 0, 1)));
			str++;
		}
		else
		{
			i = 0;
			while (ft_strchr(separator, *str) == NULL)
				buf[i++] = *str++;
			buf[i] = '\0';
			ft_lstadd_back(&list, ft_lstnew(ft_xstrdup(buf)));
		}
	}
	free(buf);
	return (list);
}
