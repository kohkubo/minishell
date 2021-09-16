/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_getall.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ywake <ywake@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 16:07:51 by kohkubo           #+#    #+#             */
/*   Updated: 2021/09/16 18:27:51 by ywake            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libhash.h"

static char	*dict_fmt_value_null(char *key)
{
	char	*s;

	s = ft_xmalloc(ft_strlen(key) + 1);
	ft_strlcpy(s, key, -1);
	return (s);
}

static char	*dict_fmt(char *key, char *value)
{
	char	*s;

	if (value == NULL)
		return (dict_fmt_value_null(key));
	s = ft_xmalloc(ft_strlen(key) + ft_strlen(value) + 2);
	ft_strlcpy(s, key, -1);
	ft_strlcat(s, "=", -1);
	ft_strlcat(s, value, -1);
	return (s);
}

char	**hash_getall(t_hash_table *h, char *(*fmt)(char *key, char *value))
{
	int			i;
	char		**all;
	char		**head;
	t_dict_item	*item;
	t_list		*lst;

	if (h == NULL)
		ft_fatal("hash_getall : Invalid argument");
	if (fmt == NULL)
		fmt = dict_fmt;
	all = ft_xmalloc(sizeof(char *) * (h->count + 1));
	head = all;
	i = -1;
	while (++i < h->tsize)
	{
		lst = h->hash_bucket[i]->lst;
		while (lst)
		{
			item = (t_dict_item *)lst->content;
			*all++ = fmt(item->key, item->value);
			lst = lst->next;
		}
	}
	*all = NULL;
	return (head);
}
