#include "libhash.h"

int	hash_getint(t_hash_table *h, char *key)
{
	char	*str;

	if (h == NULL || key == NULL)
		ft_fatal("hash_getint : Invalid argument");
	str = hash_getstr(h, key);
	if (str == NULL)
		return (0);
	return (ft_atoi(str));
}
