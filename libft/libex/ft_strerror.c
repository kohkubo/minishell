#include "libex.h"

extern const int	g_sys_nerr;
extern const char	*g_sys_errlist[];

char	*ft_strerror(int e)
{
	if (e < 0 || e >= g_sys_nerr)
		return ("Unknown error");
	else
		return ((char *)g_sys_errlist[e]);
}
