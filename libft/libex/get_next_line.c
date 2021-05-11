/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ywake <ywake@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 01:18:32 by ywake             #+#    #+#             */
/*   Updated: 2021/05/11 19:04:37 by ywake            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libex.h"

#define BUFFER_SIZE (1000)

int		myabort(char *rdbuf, char **line, char **remain)
{
	free_set((void **)&rdbuf, NULL);
	free_set((void **)line, NULL);
	free_set((void **)remain, NULL);
	return (-1);
}

int		ret(ssize_t rdrtn, char *rdbuf, char **line, char **remain)
{
	free_set((void **)&rdbuf, NULL);
	if (rdrtn > 0)
		rdrtn = 1;
	if (*line == NULL || (*remain == NULL && rdrtn != 0))
		rdrtn = myabort(rdbuf, line, remain);
	return (rdrtn);
}

int		get_next_line(int fd, char **line)
{
	char		*rdbuf;
	static char	*remain[1];
	char		*ptr;
	ssize_t		rtn;

	rdbuf = (char *)ft_xmalloc(BUFFER_SIZE + 1);
	*line = *remain;
	*remain = NULL;
	rtn = read(fd, rdbuf, BUFFER_SIZE);
	while (rtn >= 0)
	{
		rdbuf[rtn] = '\0';
		free_set((void **)line, (void **)ft_strjoin(*line, (char *)rdbuf));
		ptr = ft_strchr(*line, '\n');
		if (ptr != NULL && *line != NULL)
		{
			*remain = ft_strndup(ptr + 1, -1);
			free_set((void **)line, (void **)ft_strndup(*line, ptr - *line));
			return (ret(1, rdbuf, line, remain));
		}
		if (rtn == 0 || *line == NULL)
			return (ret(0, rdbuf, line, remain));
		rtn = read(fd, rdbuf, BUFFER_SIZE);
	}
	return (myabort(rdbuf, line, remain));
}
