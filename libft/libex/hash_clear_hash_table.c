#include "libex.h"

bool	hash_clear_table(t_hash_table **h)
{
	int	i;
	int	j;

	if (h == NULL)
		ft_fatal("hash_clear_table : Invalid argument");
	if (*h == NULL)
		return (false);
	i = 0;
	j = 0;
	while (i < (*h)->tsize)
	{
		ft_lstclear(&((*h)->hash_bucket[i]->lst), hash_clear_dict_item);
		free_set((void **)&(*h)->hash_bucket[i], NULL);
		i++;
	}
	free(*h);
	*h = NULL;
	return (true);
}
