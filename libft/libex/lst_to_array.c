#include "libex.h"

char	**lst_to_array(t_list *lst)
{
	int		len;
	char	**array;

	len = ft_lstsize(lst);
	array = ft_xmalloc(sizeof(char *) * (len + 1));
	array[len] = NULL;
	len = 0;
	while (lst)
	{
		array[len] = ft_xstrdup(lst->content);
		len++;
		lst = lst->next;
	}
	return (array);
}
