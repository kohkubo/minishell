/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kohkubo <kohkubo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 16:01:28 by kohkubo           #+#    #+#             */
/*   Updated: 2021/08/19 13:47:13 by kohkubo          ###   ########.fr       */
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
	len = ft_min_size_t(len, n);
	ptr = (char *)malloc(len + 1 * sizeof(char));
	if (ptr == NULL)
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
