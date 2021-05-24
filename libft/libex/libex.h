#ifndef LIBEX_H
# define LIBEX_H
# include "../libft/libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
# ifndef T_LIST
#  define T_LIST
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;
# endif
typedef struct s_dict_item {
	int		hash_key;
	char	*key;
	char	*value;
}	t_dict_item;
typedef struct s_hash_bucket {
	int		bcount;
	t_list	*lst;
}	t_hash_bucket;
typedef struct s_hash_table {
	int						tsize;
	int						count;
	struct s_hash_bucket	**hash_bucket;
}	t_hash_table;
int				contain(char **array, char *word);
void			free_set(void **dst, void *src);
char			**free_string_array(char **buf);
void			ft_fatal(const char *emsg);
int				ft_isspace(int c);
int				ft_strcmp(const char *s1, const char *s2);
char			*ft_strerror(int e);
char			*ft_strndup(const char *s1, size_t n);
void			*ft_xmalloc(size_t size);
int				get_next_line(int fd, char **line);
void			hash_clear_dict_item(void *item);
bool			hash_clear_table(t_hash_table **h);
bool			hash_contains_key(t_hash_table *h, char *key);
t_hash_table	*hash_create_table(int size);
void			hash_display_table(t_hash_table *h);
char			**hash_getall(t_hash_table *h);
int				hash_getint(t_hash_table *h, char *key);
char			**hash_getkeys(t_hash_table *h);
char			*hash_getstr(t_hash_table *h, char *key);
bool			hash_remove(t_hash_table *h, char *key);
t_dict_item		*hash_search(t_hash_table *h, char *key);
bool			hash_setint(t_hash_table *h, char *key, int integer);
bool			hash_setstr(t_hash_table *h, char *key, char *value);
unsigned int	hasher(const char *str, int capacity);
int				min(int a, int b);
void			strsort(char *str[], int n);
#endif
