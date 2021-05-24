#include "libex.h"

/*
** @brief Store [integer] in [key] of hash table [h].
** @return When a new "t_dict_item" is created, true is returned, otherwise false is returned.
*/
bool	hash_setint(t_hash_table *h, char *key, int integer)
{
	if (h == NULL || key == NULL)
		ft_fatal("hash_setint : Invalid argument");
	return (hash_setstr(h, key, ft_itoa(integer)));
}
