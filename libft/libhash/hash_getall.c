#include "libhash.h"

static char	*dict_fmt(char *key, char *value)
{
	char	*s;

	s = ft_substr(key, 0, ft_strlen(key) + ft_strlen(value) + 1);
	ft_strlcat(s, "=", SIZE_MAX);
	ft_strlcat(s, value, SIZE_MAX);
	return (s);
}

char	**hash_getall(t_hash_table *h)
{
	int			i;
	char		**all;
	char		**head;
	t_dict_item	*item;
	t_list		*lst;

	if (h == NULL)
		ft_fatal("hash_getall : Invalid argument");
	all = ft_xmalloc(sizeof(char *) * (h->count + 1));
	head = all;
	i = 0;
	while (i < h->tsize)
	{
		lst = h->hash_bucket[i]->lst;
		while (lst)
		{
			item = (t_dict_item *)lst->content;
			*all++ = dict_fmt(item->key, item->value);
			lst = lst->next;
		}
		i++;
	}
	*all = NULL;
	return (head);
}
