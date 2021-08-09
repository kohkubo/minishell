/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_xstrdup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kohkubo <kohkubo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 16:01:42 by kohkubo           #+#    #+#             */
/*   Updated: 2021/08/09 16:01:42 by kohkubo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libex.h"

char	*ft_xstrdup(const char *s1)
{
	char	*dst;

	dst = ft_xmalloc(ft_strlen(s1) + 1);
	ft_strlcpy(dst, s1, ULLONG_MAX);
	return (dst);
}
