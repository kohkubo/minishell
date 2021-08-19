/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_hash_display_table.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kohkubo <kohkubo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 16:00:32 by kohkubo           #+#    #+#             */
/*   Updated: 2021/08/19 13:25:00 by kohkubo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libdebug.h"

static void	display_dict_item(void *content)
{
	t_dict_item	*item;

	item = (t_dict_item *)content;
	printf("hash_key : %d\n", item->hash_key);
	printf("key      : '%s'\n", item->key);
	printf("value    : '%s'\n", item->value);
	printf("+++++++\n");
}

/*
** @brief for debug.
*/
void	debug_hash_display_table(t_hash_table *h)
{
	int	i;

	if (h == NULL)
	{
		printf("No table!!\n");
		return ;
	}
	printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
	printf("hash_table size       : %d\n", h->tsize);
	printf("hash_table item count : %d\n", h->count);
	printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
	i = 0;
	while (i < h->tsize)
	{
		printf("=== hash_bucket : %d (%d) ===\n", i, h->hash_bucket[i]->bcount);
		if (h->hash_bucket[i]->bcount)
			ft_lstiter(h->hash_bucket[i]->lst, display_dict_item);
		i++;
	}
}


