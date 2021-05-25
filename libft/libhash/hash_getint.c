#include "libhash.h"

/*
** @brief Get the integer value stored in [key], and contain to [ret].
** @return Returns ture if successful, false otherwise.
*/
bool	hash_getint(t_hash_table *h, char *key, int *ret)
{
	char	*str;

	if (h == NULL || key == NULL)
		ft_fatal("hash_getint : Invalid argument");
	str = hash_getstr(h, key);
	if (str == NULL)
		return (false);
	*ret = ft_atoi(str);
	return (true);
}
