/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kohkubo <kohkubo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 20:23:32 by kohkubo           #+#    #+#             */
/*   Updated: 2021/08/16 21:17:45 by kohkubo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	env_init()
{
	extern char	**environ;
	size_t		i;
	char		*tmp;
	
	i = 0;
	while (environ[i] != NULL)
	{
		tmp = ft_strdup(environ[i]);
		tmp[ft_strchr(tmp, '=') - tmp] = '\0';
		hash_setstr(g_shell.hash, tmp, tmp + ft_strlen(tmp) + 1);
		free_set((void **)&tmp, NULL);
		i++;
	}
}

void	minishell_init()
{
	g_shell.hash = hash_create_table(10);
	env_init();
}
