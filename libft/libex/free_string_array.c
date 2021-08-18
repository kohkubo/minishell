/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_string_array.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ywake <ywake@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 15:53:50 by ywake             #+#    #+#             */
/*   Updated: 2021/08/09 15:53:51 by ywake            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libex.h"

char	**free_string_array(char **buf)
{
	size_t	i;

	i = 0;
	while (buf[i])
	{
		free(buf[i]);
		buf[i] = NULL;
		i++;
	}
	free(buf);
	return (NULL);
}
