/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fatal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kohkubo <kohkubo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 16:01:07 by kohkubo           #+#    #+#             */
/*   Updated: 2021/08/09 16:01:07 by kohkubo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libex.h"
#include <string.h>

void	ft_fatal(const char *emsg)
{
	ft_putstr_fd("fatal: ", 2);
	if (emsg == NULL)
		ft_putendl_fd(strerror(errno), 2);
	else
	{
		if (errno)
		{
			ft_putstr_fd((char *)emsg, 2);
			ft_putendl_fd(strerror(errno), 2);
		}
		else
			ft_putendl_fd((char *)emsg, 2);
	}
	exit(1);
}
