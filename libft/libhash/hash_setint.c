/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_setint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kohkubo <kohkubo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 16:08:05 by kohkubo           #+#    #+#             */
/*   Updated: 2021/08/09 16:08:06 by kohkubo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libhash.h"

/*
** @brief Store [integer] in [key] of hash table [h].
** @return When a new "t_dict_item" is created, true is returned, otherwise
false is returned.
*/
bool	hash_setint(t_hash_table *h, char *key, int integer)
{
	char	*str;
	bool	ret;

	if (h == NULL || key == NULL)
		ft_fatal("hash_setint : Invalid argument");
	str = ft_itoa(integer);
	ret = hash_setstr(h, key, str);
	free(str);
	str = NULL;
	return (ret);
}
