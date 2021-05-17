#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	void	*head;

	head = dst;
	if (!src && !dst)
		return (NULL);
	while (0 < n--)
		*(unsigned char *)dst++ = *(unsigned char *)src++;
	return (head);
}
