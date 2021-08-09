/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_array_sort.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kohkubo <kohkubo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 16:00:17 by kohkubo           #+#    #+#             */
/*   Updated: 2021/08/09 16:00:19 by kohkubo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "libdebug.h"

static int	compare(const void *a, const void *b)
{
	return ft_strcmp(*(const char **)a, *(const char **)b);
}

void	qsort_strarray(char **array)
{
	qsort(array, arraylen(array), sizeof(char *), compare);
}
