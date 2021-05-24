#include "libex.h"

char	*hash_getstr(t_hash_table *h, char *key)
{
	t_list	*lst;

	if (h == NULL || key == NULL)
		ft_fatal("hash_getstr : Invalid argument");
	lst = hash_search(h, key);
	if (lst == NULL)
		return (NULL);
	return (((t_dict_item *)lst->content)->value);
}
