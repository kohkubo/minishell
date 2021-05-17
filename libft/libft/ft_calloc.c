#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*dst;
	size_t	len;

	len = count * size;
	dst = malloc(len);
	if (!dst)
		return (NULL);
	ft_bzero(dst, len);
	return (dst);
}
