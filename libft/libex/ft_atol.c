#include "libex.h"

static long	ft_atol_overflow(int neg)
{
	errno = EINVAL;
	if (neg == 1)
		return (LONG_MAX);
	else
		return (LONG_MIN);
}

static bool	is_uadd_overflow(unsigned long a, unsigned long b)
{
	if (a > ULONG_MAX - b)
		return (true);
	return (false);
}

static bool	is_umul_overflow(unsigned long a, unsigned long b)
{
	if (a > ULONG_MAX / b)
		return (true);
	return (false);
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
	while (*s == '0')
		s++;
	while (ft_isdigit(*s))
	{
		tmp = n * 10;
		if (is_umul_overflow(n, 10) || is_uadd_overflow(tmp, *s - '0'))
			return (ft_atol_overflow(neg));
		n = tmp + *s++ - '0';
		if (LONG_MAX < (n - (neg < 0)))
			return (ft_atol_overflow(neg));
	}
	return ((long)(n * neg));
}
