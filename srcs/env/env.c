/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kohkubo <kohkubo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 20:23:32 by kohkubo           #+#    #+#             */
/*   Updated: 2021/08/19 12:19:36 by kohkubo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	store_shellenv(char **arr)
{
	char		*tmp;
	size_t		i;

	i = 0;
	while (arr[i] != NULL)
	{
		if (ft_strchr(arr[i], '=') != NULL)
		{
			tmp = ft_strdup(arr[i]);
			tmp[ft_strchr(tmp, '=') - tmp] = '\0';
			hash_setstr(g_shell.hash, tmp, tmp + ft_strlen(tmp) + 1);
			free_set((void **)&tmp, NULL);
		}
		i++;
	}
}

static void	env_init(void)
{
	extern char	**environ;

	store_shellenv(environ);
}

void	minishell_init(void)
{
	g_shell.hash = hash_create_table(10);
	env_init();
}
