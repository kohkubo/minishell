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

int	main(void)
{
	char	*input;

	input = NULL;
	while (1)
	{
		if (get_next_line(0, &input) <= 0)
			break ;
		parse(input);
		free_set((void **)&input, NULL);
	}
	free_set((void **)&input, NULL);
	return (0);
}
