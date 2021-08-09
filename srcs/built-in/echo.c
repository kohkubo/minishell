/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kohkubo <kohkubo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 16:06:28 by kohkubo           #+#    #+#             */
/*   Updated: 2021/08/09 16:06:29 by kohkubo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

static void	ft_echo_exit_check(char **args)
{
	if (*args == NULL)
	{
		printf("\n");
		exit(0);
	}
}

int	ft_echo(char **args)
{
	bool	op_flg;

	op_flg = false;
	if (args == NULL)
		return (1);
	ft_echo_exit_check(args);
	if (!ft_strncmp(*args, "-", SIZE_MAX))
		ft_echo_exit_check(++args);
	else if (!ft_strncmp(*args, "-n", SIZE_MAX))
	{
		op_flg = true;
		if (*++args == NULL)
			return (0);
	}
	printf("%s", *args++);
	while (*args)
	{
		printf(" %s", *args);
		args++;
	}
	if (op_flg == false)
		printf("\n");
	return (0);
}
