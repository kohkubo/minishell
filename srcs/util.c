#include "shell.h"

char	*ft_xsubstr(const char *s, unsigned int start, size_t len)
{
	return (catch_null(ft_substr(s, start, len), "ft_substr"));
}

t_list	*ft_xlstnew(void *content)
{
	return (catch_null(ft_lstnew(content), "ft_lstnew"));
}

char	*wrapper_hash_getstr(t_hash_table *h, char *key)
{
	char	*tmp;

	tmp = (char *)hash_getstr(h, key);
	if (tmp == NULL)
		return ("");
	return (tmp);
}
