/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kohkubo <kohkubo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 20:23:32 by kohkubo           #+#    #+#             */
/*   Updated: 2021/08/23 16:54:25 by kohkubo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	store_shellenv(char **arr, t_hash_table *table)
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
			hash_setstr(table, tmp, tmp + ft_strlen(tmp) + 1);
			free_set((void **)&tmp, NULL);
		}
		i++;
	}
}

static void	env_init(void)
{
	extern char	**environ;

	store_shellenv(environ, g_shell.env);
}

void	minishell_init(void)
{
	g_shell.env = hash_create_table(10);
	env_init();
}
