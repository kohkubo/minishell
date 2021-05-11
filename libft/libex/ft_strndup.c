/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ywake <ywake@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 05:49:41 by ywake             #+#    #+#             */
/*   Updated: 2021/05/11 19:04:14 by ywake            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libex.h"

char	*ft_strndup(const char *s1, size_t n)
{
	char	*ptr;
	size_t	len;
	size_t	i;

	if (s1 == NULL)
		return (NULL);
	len = 0;
	while (s1[len] != '\0')
		len++;
	len = (len < n) ? len : n;
	if ((ptr = (char *)malloc(len + 1 * sizeof(char))) == NULL)
		return (NULL);
	i = 0;
	while (s1[i] != '\0' && i < len)
	{
		ptr[i] = s1[i];
		i++;
	}
	ptr[i] = 0;
	return (ptr);
}
