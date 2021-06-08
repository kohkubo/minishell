#include "libhash.h"

static char	*return_null_free(char *s)
{
	free(s);
	return (NULL);
}

static void	*dict_info(int hash_key, char *key, char *value)
{
	t_dict_item	*dict;

	dict = ft_xmalloc(sizeof(t_dict_item));
	dict->hash_key = hash_key;
	dict->key = ft_xstrdup(key);
	if (value != NULL)
		dict->value = ft_xstrdup(value);
	else
		dict->value = NULL;
	return ((void *)dict);
}

/*
** @brief Store [value] in [key] of hash table [h].
** @return When a new "t_dict_item" is created, true is returned,
 otherwise false is returned.
*/
bool	hash_setstr(t_hash_table *h, char *key, char *value)
{
	int			index;
	t_list		*newlst;
	t_dict_item	*item;

	if (h == NULL || key == NULL)
		ft_fatal("hash_setstr : Invalid argument");
	item = hash_search(h, key);
	if (item)
	{
		item->value = return_null_free(item->value);
		if (value != NULL)
			item->value = ft_xstrdup(value);
		return (false);
	}
	else
	{
		index = hasher(key, h->tsize);
		newlst = ft_lstnew(dict_info(index, key, value));
		ft_lstadd_front(&h->hash_bucket[index]->lst, newlst);
		h->hash_bucket[index]->bcount++;
		h->count++;
	}
	return (true);
}
