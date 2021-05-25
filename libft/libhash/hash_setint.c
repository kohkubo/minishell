#include "libhash.h"

/*
** @brief Store [integer] in [key] of hash table [h].
** @return When a new "t_dict_item" is created, true is returned, otherwise
false is returned.
*/
bool	hash_setint(t_hash_table *h, char *key, int integer)
{
	char	*str;
	bool	ret;

	if (h == NULL || key == NULL)
		ft_fatal("hash_setint : Invalid argument");
	str = ft_itoa(integer);
	ret = hash_setstr(h, key, str);
	free(str);
	str = NULL;
	return (ret);
}
