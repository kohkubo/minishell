#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*elem;

	if (!content)
		return (NULL);
	elem = malloc(sizeof(t_list));
	if (!elem)
		return (0);
	elem->content = content;
	elem->next = NULL;
	return (elem);
}
