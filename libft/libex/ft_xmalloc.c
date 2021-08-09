/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_xmalloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kohkubo <kohkubo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 16:01:34 by kohkubo           #+#    #+#             */
/*   Updated: 2021/08/09 16:01:35 by kohkubo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libex.h"

static void	ft_fatalx(const char *emsg)
{
	errno = 0;
	ft_fatal(emsg);
}

void	*ft_xmalloc(size_t size)
{
	void	*ptr;

	if (size == 0)
		ft_fatalx("xmalloc: zero size");
	ptr = malloc(size);
	if (ptr == NULL)
		ft_fatal("xmalloc: ");
	return (ptr);
}
