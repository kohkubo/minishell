#include "libhash.h"

t_hash_table	*hash_create_table(int size)
{
	t_hash_table	*h;
	int				i;

	if (size < 1)
		return (NULL);
	h = ft_xmalloc(sizeof(t_hash_table));
	h->tsize = size;
	h->count = 0;
	i = 0;
	h->hash_bucket = ft_xmalloc(sizeof(t_hash_bucket *) * h->tsize);
	while (i < h->tsize)
	{
		h->hash_bucket[i] = ft_xmalloc(sizeof(t_hash_bucket));
		h->hash_bucket[i]->lst = NULL;
		h->hash_bucket[i]->bcount = 0;
		i++;
	}
	return (h);
}
