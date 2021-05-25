#include "libhash.h"

t_dict_item	*hash_search(t_hash_table *h, char *key)
{
	t_list	*lst;

	if (h == NULL || key == NULL)
		ft_fatal("hash_search : Invalid argument");
	lst = h->hash_bucket[hasher(key, h->tsize)]->lst;
	while (lst)
	{
		if (!ft_strcmp(((t_dict_item *)lst->content)->key, key))
			return (lst->content);
		lst = lst->next;
	}
	return (NULL);
}
