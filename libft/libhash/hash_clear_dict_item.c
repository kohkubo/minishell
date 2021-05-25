#include "libhash.h"

void	hash_clear_dict_item(void *item)
{
	t_dict_item	*dict;

	if (item == NULL)
		return ;
	dict = (t_dict_item *)item;
	dict->hash_key = 0;
	free(dict->key);
	dict->key = NULL;
	free(dict->value);
	dict->value = NULL;
	free(item);
}
