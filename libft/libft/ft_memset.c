#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	void	*head;

	head = b;
	while (len--)
		*(unsigned char *)b++ = (unsigned char)c;
	return (head);
}
