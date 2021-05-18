#include "libex.h"

#define BUFFER_SIZE (1000)

static int	myabort(char *rdbuf, char **line, char **remain)
{
	free_set((void **)&rdbuf, NULL);
	free_set((void **)line, NULL);
	free_set((void **)remain, NULL);
	return (-1);
}

static int	ret(ssize_t rdrtn, char *rdbuf, char **line, char **remain)
{
	free_set((void **)&rdbuf, NULL);
	if (rdrtn > 0)
		rdrtn = 1;
	if (*line == NULL || (*remain == NULL && rdrtn != 0))
		rdrtn = myabort(rdbuf, line, remain);
	return (rdrtn);
}

static char	*safe_strjoin(char const *s1, char const *s2)
{
	char	*str;
	char	*head;

	if (!s1)
		s1 = "";
	if (!s2)
		s2 = "";
	str = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!str)
		return (NULL);
	head = str;
	while (*s1)
		*str++ = *s1++;
	while (*s2)
		*str++ = *s2++;
	*str = '\0';
	return (head);
}

int	get_next_line(int fd, char **line)
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
		free_set((void **)line, safe_strjoin(*line, (char *)rdbuf));
		ptr = ft_strchr(*line, '\n');
		if (ptr != NULL && *line != NULL)
		{
			*remain = ft_strndup(ptr + 1, -1);
			free_set((void **)line, ft_strndup(*line, ptr - *line));
			return (ret(1, rdbuf, line, remain));
		}
		if (rtn == 0 || *line == NULL)
			return (ret(0, rdbuf, line, remain));
		rtn = read(fd, rdbuf, BUFFER_SIZE);
	}
	return (myabort(rdbuf, line, remain));
}
