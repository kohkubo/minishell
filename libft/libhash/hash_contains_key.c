#include "libhash.h"

bool	hash_contains_key(t_hash_table *h, char *key)
{
	t_dict_item	*item;

	if (h == NULL || key == NULL)
		ft_fatal("hash_contains_key : Invalid argument");
	item = hash_search(h, key);
	if (item)
		return (true);
	return (false);
}
