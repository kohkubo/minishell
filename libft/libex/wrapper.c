#include "libex.h"

char	*ft_xsubstr(const char *s, unsigned int start, size_t len)
{
	return (catch_null(ft_substr(s, start, len), "ft_substr"));
}

t_list	*ft_xlstnew(void *content)
{
	return (catch_null(ft_lstnew(content), "ft_lstnew"));
}

char	*ft_xstrdup(const char *s1)
{
	return (catch_null(ft_strdup(s1), "ft_strdup"));
}

char	*ft_xstrjoin(char const *s1, char const *s2)
{
	return (catch_null(ft_strjoin(s1, s2), "ft_strjoin"));
}
