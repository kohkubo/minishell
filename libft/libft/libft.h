#ifndef LIBFT_H
# define LIBFT_H
# include "../libex/libex.h"
# include <unistd.h>
# include <stdlib.h>
// Prototypes
size_t	ft_strlen(const char *s);
void	ft_putstr_fd(char *s, int fd);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strchr(const char *s, int c);
void	ft_putendl_fd(char *s, int fd);
#endif
