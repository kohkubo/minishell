/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_xmalloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ywake <ywake@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 18:03:49 by ywake             #+#    #+#             */
/*   Updated: 2021/05/11 18:05:28 by ywake            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libex.h"

void	*ft_xmalloc(size_t size)
{
	void	*ptr;

	if (size == 0)
		exit(1);
	ptr = malloc(size);
	if (ptr == NULL)
		exit(1);
	return (ptr);
}
