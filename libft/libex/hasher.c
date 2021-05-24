#include "libex.h"

unsigned int	hasher(const char *str, int capacity)
{
	unsigned int	hashval;
	char			*tmp;
	char			*head;

	tmp = ft_strdup(str);
	head = tmp;
	hashval = 2166136261UL;
	while (*tmp)
	{
		hashval *= 16777619UL;
		hashval ^= *((unsigned char *)tmp++);
	}
	free(head);
	return (hashval % capacity);
}
