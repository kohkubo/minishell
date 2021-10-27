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
	unsigned long	n;
	int				neg;
	unsigned long	tmp;

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
		if (LONG_MAX < (n - (neg < 0)))
			return (ft_atol_overflow(neg));
	}
	return ((long)n * neg);
}
