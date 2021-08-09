/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strsort.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kohkubo <kohkubo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 16:02:15 by kohkubo           #+#    #+#             */
/*   Updated: 2021/08/09 16:02:16 by kohkubo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libex.h"

static void	strswap(char **a, char **b)
{
	char	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	strsort(char *str[], int n)
{
	int	i;
	int	j;

	i = 0;
	while (i < n)
	{
		j = i + 1;
		while (j < n)
		{
			if ((ft_strcmp(str[j], str[i])) < 0)
				strswap(&str[i], &str[j]);
			j++;
		}
		i++;
	}
}
