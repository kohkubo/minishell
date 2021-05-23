#ifndef LIBEX_H
# define LIBEX_H
# include "../libft/libft.h"
# include <stdlib.h>
void			ft_fatal(const char *emsg);
int				ft_strcmp(const char *s1, const char *s2);
char			*ft_strerror(int e);
void			*ft_xmalloc(size_t size);
#endif
