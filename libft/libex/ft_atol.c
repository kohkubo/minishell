#include "libex.h"

static long	ft_atol_overflow(int neg)
{
	errno = EINVAL;
	if (neg == 1)
		return (LONG_MAX);
	else
		return (LONG_MIN);
}

long	ft_atol(const char *s)
{
	long	n;
	int		neg;
	long	tmp;

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
			return (ft_atol_overflow(neg));
	}
	return ((n * neg));
}
