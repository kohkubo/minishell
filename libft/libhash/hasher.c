/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hasher.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kohkubo <kohkubo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 16:08:10 by kohkubo           #+#    #+#             */
/*   Updated: 2021/08/09 16:08:11 by kohkubo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libhash.h"

/*
** FNV-1 hash
*/
unsigned int	hasher(const char *str, int capacity)
{
	unsigned int	hashval;

	hashval = 2166136261UL;
	while (*str)
	{
		hashval *= 16777619UL;
		hashval ^= *((unsigned char *)str++);
	}
	return (hashval % capacity);
}
