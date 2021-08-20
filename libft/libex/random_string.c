/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kohkubo <kohkubo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 13:57:46 by kohkubo           #+#    #+#             */
/*   Updated: 2021/08/19 13:57:47 by kohkubo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libex.h"

char	*random_string(size_t size)
{
	char	*char_set;
	char	*str;
	size_t	i;

	char_set = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	str = ft_xmalloc(size + 1);
	i = 0;
	while (i < size)
	{
		str[i] = char_set[rand() % 62];
		i++;
	}
	str[i] = '\0';
	return (str);
}
