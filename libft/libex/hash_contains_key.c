#include "libex.h"

bool	hash_contains_key(t_hash_table *h, char *key)
{
	t_list	*lst;

	if (h == NULL || key == NULL)
		ft_fatal("hash_contains_key : Invalid argument");
	lst = h->hash_bucket[hasher(key, h->tsize)]->lst;
	while (lst)
	{
		if (!ft_strcmp(((t_dict_item *)lst->content)->key, key))
			return (true);
		lst = lst->next;
	}
	return (false);
}
