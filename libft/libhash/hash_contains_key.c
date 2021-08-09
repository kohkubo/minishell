/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_contains_key.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kohkubo <kohkubo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 16:07:47 by kohkubo           #+#    #+#             */
/*   Updated: 2021/08/09 16:07:47 by kohkubo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libhash.h"

bool	hash_contains_key(t_hash_table *h, char *key)
{
	t_dict_item	*item;

	if (h == NULL || key == NULL)
		ft_fatal("hash_contains_key : Invalid argument");
	item = hash_search(h, key);
	if (item)
		return (true);
	return (false);
}
