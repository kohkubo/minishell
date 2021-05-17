#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *newobj)
{
	t_list	*last;

	if (!lst || !newobj)
		return ;
	if (*lst)
	{
		last = ft_lstlast(*lst);
		last->next = newobj;
	}
	else
		*lst = newobj;
}
