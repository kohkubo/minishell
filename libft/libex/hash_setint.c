#include "libex.h"

bool	hash_setint(t_hash_table *h, char *key, int integer)
{
	if (h == NULL || key == NULL)
		ft_fatal("hash_setint : Invalid argument");
	return (hash_setstr(h, key, ft_itoa(integer)));
}
