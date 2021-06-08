#include "libhash.h"

/*
** @brief Get the integer value stored in [key], and contain to [ret].
** @return Returns ture if successful, false otherwise.
*/
bool	hash_getint(t_hash_table *h, char *key, int *ret)
{
	t_dict_item	*item;

	if (h == NULL || key == NULL || ret == NULL)
		ft_fatal("hash_getint : Invalid argument");
	item = hash_search(h, key);
	if (item == NULL)
		return (false);
	if (item->value == NULL)
		*ret = 0;
	else
		*ret = ft_atoi(item->value);
	return (true);
}
