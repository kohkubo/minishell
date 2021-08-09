/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_create_table.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kohkubo <kohkubo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 16:07:49 by kohkubo           #+#    #+#             */
/*   Updated: 2021/08/09 16:07:49 by kohkubo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libhash.h"

t_hash_table	*hash_create_table(int size)
{
	t_hash_table	*h;
	int				i;

	if (size < 1)
		return (NULL);
	h = ft_xmalloc(sizeof(t_hash_table));
	h->tsize = size;
	h->count = 0;
	i = 0;
	h->hash_bucket = ft_xmalloc(sizeof(t_hash_bucket *) * h->tsize);
	while (i < h->tsize)
	{
		h->hash_bucket[i] = ft_xmalloc(sizeof(t_hash_bucket));
		h->hash_bucket[i]->lst = NULL;
		h->hash_bucket[i]->bcount = 0;
		i++;
	}
	return (h);
}
