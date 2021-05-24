#include "libex.h"

char	*hash_getstr(t_hash_table *h, char *key)
{
	t_dict_item	*item;

	if (h == NULL || key == NULL)
		ft_fatal("hash_getstr : Invalid argument");
	item = hash_search(h, key);
	if (item == NULL)
		return (NULL);
	return (((t_dict_item *)item)->value);
}
