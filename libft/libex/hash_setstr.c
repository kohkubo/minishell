#include "libex.h"

static void	*dict_info(int hash_key, char *key, char *value)
{
	t_dict_item	*dict;

	dict = ft_xmalloc(sizeof(t_dict_item));
	dict->hash_key = hash_key;
	dict->key = ft_strdup(key);
	dict->value = ft_strdup(value);
	return ((void *)dict);
}

bool	hash_setstr(t_hash_table *h, char *key, char *value)
{
	int			index;
	t_list		*newlst;
	t_dict_item	*item;

	if (h == NULL || key == NULL || value == NULL)
		ft_fatal("hash_setstr : Invalid argument");
	newlst = hash_search(h, key);
	if (newlst)
	{
		item = (t_dict_item *)newlst->content;
		free(item->value);
		item->value = ft_strdup(value);
		return (false);
	}
	else
	{
		index = hasher(key, h->tsize);
		newlst = ft_lstnew(dict_info(index, key, value));
		ft_lstadd_back(&h->hash_bucket[index]->lst, newlst);
		h->hash_bucket[index]->bcount++;
		h->count++;
	}
	return (true);
}
