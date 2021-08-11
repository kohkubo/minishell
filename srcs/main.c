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

#include "../includes/shell.h"

t_shell	g_all;
char	*shell_prompt(t_state_type state)
{
	if (state == STATE_GENERAL)
		return (SHELL_PROMPT);
	else if (state == STATE_IN_HEREDOC)
		return (SHELL_HEREDOC);
	else if (state == STATE_IN_DQUOTE)
		return (SHELL_DQUOTE);
	else if (state == STATE_IN_QUOTE)
		return (SHELL_QUOTE);
}

int	main(void)
{
	char	*input;

	input = NULL;
	while (1)
	{
		input = readline(SHELL_PROMPT);
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
