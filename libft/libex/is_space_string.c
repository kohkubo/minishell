#include "libex.h"

bool	is_space_string(char *s)
{
	while (ft_isspace(*s++))
		;
	return (!*s);
}
