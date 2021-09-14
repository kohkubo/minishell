#include "libex.h"

char	*lst_to_string(t_list *lst)
{
	char	*tmp;

	if (lst == NULL)
		ft_fatal("lst_to_string: Invalid argument");
	tmp = ft_xstrdup("");
	while (lst)
	{
		if (lst->content != NULL)
			free_set((void **)&tmp, ft_xstrjoin(tmp, lst->content));
		lst = lst->next;
	}
	return (tmp);
}
