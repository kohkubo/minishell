#include "libex.h"

char	**hash_getkeys(t_hash_table *h)
{
	int			i;
	char		**all;
	char		**head;
	t_dict_item	*item;
	t_list		*lst;

	if (h == NULL)
		ft_fatal("hash_getkeys : Invalid argument");
	all = ft_xmalloc(sizeof(char *) * (h->count + 1));
	head = all;
	i = 0;
	while (i < h->tsize)
	{
		lst = h->hash_bucket[i]->lst;
		while (lst)
		{
			item = (t_dict_item *)lst->content;
			*all++ = ft_strdup(item->key);
			lst = lst->next;
		}
		i++;
	}
	*all = NULL;
	strsort(head, h->count);
	return (head);
}
