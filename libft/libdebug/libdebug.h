#ifndef LIBDEBUG_H
# define LIBDEBUG_H
# include "../libft/libft.h"
# include "../libex/libex.h"
# include "../libhash/libhash.h"

int		arraylen(char **array);
void	display_array(char **array);
int		array_cmp(char **aa, char **bb);
char	**str_array_dup(char **array);
void	qsort_strarray(char **array);
void	debug_hash_display_table(t_hash_table *h);
char	*debug_rand_text(size_t size);

#endif
