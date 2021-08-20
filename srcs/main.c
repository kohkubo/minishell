/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ywake <ywake@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 15:50:29 by ywake             #+#    #+#             */
/*   Updated: 2021/08/09 15:50:30 by ywake            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_shell	g_shell;

int	main(void)
{
	char	*input;

	minishell_init();
	input = NULL;
	while (1)
	{
		input = readline(PROMPT);
		if (input == NULL || ft_strlen(input) == 0)
		{
			free_set((void **)&input, NULL);
			break ;
		}
		add_history(input);
		parse(input);
		free_set((void **)&input, NULL);
	}
	return (0);
}
