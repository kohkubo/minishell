/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_array.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kohkubo <kohkubo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 16:00:24 by kohkubo           #+#    #+#             */
/*   Updated: 2021/08/19 11:43:07 by kohkubo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libdebug.h"

/*
** @brief Compares two string arrays.
** @return If there is no difference returns -1,
** find difference returns the index.
*/
int	array_cmp(char **aa, char **bb)
{
	int	i;

	i = 0;
	while (aa[i] || bb[i])
	{
		if (!(aa[i] && bb[i]))
		{
			printf("[index: %d] %s : %s\n", i, aa[i], bb[i]);
			return (i);
		}
		if (ft_strcmp(aa[i], bb[i]))
		{
			printf("[index: %d] %s : %s\n", i, aa[i], bb[i]);
			return (i);
		}
		i++;
	}
	return (-1);
}

char	**str_array_dup(char **array)
{
	int		i;
	char	**ss;
	char	**head;

	ss = calloc(sizeof(char *), arraylen(array) + 1);
	head = ss;
	i = 0;
	while (array[i])
	{
		ss[i] = ft_strdup(array[i]);
		i++;
	}
	ss[i] = 0;
	return (head);
}
