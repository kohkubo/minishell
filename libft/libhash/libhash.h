/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libhash.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kohkubo <kohkubo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 16:08:13 by kohkubo           #+#    #+#             */
/*   Updated: 2021/09/07 17:09:17 by kohkubo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBHASH_H
# define LIBHASH_H
# include "../libft/libft.h"
# include "../libex/libex.h"
# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>

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

bool			hash_contains_key(t_hash_table *h, char *key);
unsigned int	hasher(const char *str, int capacity);
bool			hash_remove(t_hash_table *h, char *key);
char			**hash_getkeys(t_hash_table *h);
bool			hash_setstr(t_hash_table *h, char *key, char *value);
const char		*hash_getstr(t_hash_table *h, char *key);
t_dict_item		*hash_search(t_hash_table *h, char *key);
void			hash_clear_dict_item(void *item);
char			**hash_getall(t_hash_table *h, char *(*fmt)(char *k, char *v));
bool			hash_setint(t_hash_table *h, char *key, int integer);
bool			hash_clear_table(t_hash_table **h);
bool			hash_getint(t_hash_table *h, char *key, int *ret);
t_hash_table	*hash_create_table(int size);
void			debug_hash_display_table(t_hash_table *h);

#endif
