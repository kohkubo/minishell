#include "libhash.h"

static void	hash_table_count_decrement(t_hash_table *h, t_hash_bucket *b)
{
	b->bcount--;
	h->count--;
}

static bool	hash_remove_lst_first(t_hash_table *h, t_hash_bucket *b, char *key)
{
	t_list	*first;
	t_list	*tmp;

	first = b->lst;
	if (!ft_strcmp(((t_dict_item *)first->content)->key, key))
	{
		tmp = first->next;
		ft_lstdelone(first, hash_clear_dict_item);
		b->lst = tmp;
		hash_table_count_decrement(h, b);
		return (true);
	}
	return (false);
}

/*
** @brief Remove [key] of hash table [h].
** @return return true if removed, false otherwise.
*/
bool	hash_remove(t_hash_table *h, char *key)
{
	t_hash_bucket	*b;
	t_list			*lst;
	t_list			*tmp;

	if (h == NULL || key == NULL)
		ft_fatal("hash_remove : Invalid argument");
	b = h->hash_bucket[hasher(key, h->tsize)];
	lst = b->lst;
	if (lst == NULL)
		return (false);
	if (hash_remove_lst_first(h, b, key))
		return (true);
	while (lst && lst->next)
	{
		if (!ft_strcmp(((t_dict_item *)lst->next->content)->key, key))
		{
			tmp = lst->next->next;
			ft_lstdelone(lst->next, hash_clear_dict_item);
			lst->next = tmp;
			hash_table_count_decrement(h, b);
			return (true);
		}
		lst = lst->next;
	}
	return (false);
}
