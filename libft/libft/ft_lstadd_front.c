#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *newobj)
{
	if (lst)
	{
		if (*lst)
			newobj->next = *lst;
		*lst = newobj;
	}
}
