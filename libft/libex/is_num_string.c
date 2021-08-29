#include "libex.h"

bool	is_num_string(char *s)
{
	if (*s == '-' || *s == '+')
		s++;
	while (*s)
		if (!ft_isdigit(*s++))
			return (false);
	return (true);
}
