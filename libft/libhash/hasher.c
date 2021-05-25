#include "libhash.h"

/*
** FNV-1 hash
*/
unsigned int	hasher(const char *str, int capacity)
{
	unsigned int	hashval;

	hashval = 2166136261UL;
	while (*str)
	{
		hashval *= 16777619UL;
		hashval ^= *((unsigned char *)str++);
	}
	return (hashval % capacity);
}
