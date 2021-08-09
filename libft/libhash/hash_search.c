/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_search.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kohkubo <kohkubo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 16:08:03 by kohkubo           #+#    #+#             */
/*   Updated: 2021/08/09 16:08:04 by kohkubo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libhash.h"

t_dict_item	*hash_search(t_hash_table *h, char *key)
{
	t_list	*lst;

	if (h == NULL || key == NULL)
		ft_fatal("hash_search : Invalid argument");
	lst = h->hash_bucket[hasher(key, h->tsize)]->lst;
	while (lst)
	{
		if (!ft_strcmp(((t_dict_item *)lst->content)->key, key))
			return (lst->content);
		lst = lst->next;
	}
	return (NULL);
}
