/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_getstr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kohkubo <kohkubo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 16:07:59 by kohkubo           #+#    #+#             */
/*   Updated: 2021/09/07 17:03:16 by kohkubo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libhash.h"

/*
** @brief Returns the string value stored in [key].
** @return Returns string if successful, NULL otherwise.
*/
const char	*hash_getstr(t_hash_table *h, char *key)
{
	t_dict_item	*item;

	if (h == NULL || key == NULL)
		ft_fatal("hash_getstr : Invalid argument");
	item = hash_search(h, key);
	if (item == NULL)
		return (NULL);
	return (((t_dict_item *)item)->value);
}
