#include "libft.h"

int	ft_atoi(const char *s)
{
	uint64_t	n;
	int			neg;
	uint64_t	tmp;

	n = 0;
	neg = 1;
	while (ft_isspace(*s))
		s++;
	if (*s == '-' || *s == '+')
		if (*s++ == '-')
			neg = -1;
	while (ft_isdigit(*s))
	{
		tmp = n;
		n = n * 10 + *s++ - '0';
		if (tmp >> 60 || n >> 63)
		{
			errno = EINVAL;
			if (neg == 1)
				return ((int)LONG_MAX);
			else
				return ((int)LONG_MIN);
		}
	}
	return ((int)(n * neg));
}
