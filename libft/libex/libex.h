#ifndef LIBEX_H
# define LIBEX_H
# include "../libft/libft.h"
# include <stdlib.h>
int		contain(char **array, char *word);
void	free_set(void **dst, void *src);
char	**free_string_array(char **buf);
int		ft_isspace(int c);
char	*ft_strndup(const char *s1, size_t n);
void	*ft_xmalloc(size_t size);
int		get_next_line(int fd, char **line);
int		min(int a, int b);
#endif
