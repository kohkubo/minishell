/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_clear_dict_item.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kohkubo <kohkubo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 16:07:41 by kohkubo           #+#    #+#             */
/*   Updated: 2021/08/09 16:07:42 by kohkubo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libhash.h"

void	hash_clear_dict_item(void *item)
{
	t_dict_item	*dict;

	if (item == NULL)
		return ;
	dict = (t_dict_item *)item;
	dict->hash_key = 0;
	free(dict->key);
	dict->key = NULL;
	free(dict->value);
	dict->value = NULL;
	free(item);
}
