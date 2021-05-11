#ifndef LIBEX_H
# define LIBEX_H
# include "../libft/libft.h"
# include <stdlib.h>
// Prototypes
void	*ft_xmalloc(size_t size);
void	free_set(void **dst, void *src);
char	*ft_strndup(const char *s1, size_t n);
int		get_next_line(int fd, char **line);
#endif
