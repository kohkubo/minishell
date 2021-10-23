#include "libex.h"

t_list	*separate_to_lst(char *str, char *separator)
{
	t_list	*lst;
	char	*start;

	lst = NULL;
	while (*str != '\0')
	{
		if (ft_strchr(separator, *str) != NULL)
		{
			ft_lstadd_back(&lst, ft_lstnew(ft_xsubstr(str, 0, 1)));
			str++;
		}
		else
		{
			start = str;
			while (ft_strchr(separator, *str) == NULL)
				str++;
			ft_lstadd_back(&lst, ft_lstnew(ft_xsubstr(start, 0, str - start)));
		}
	}
	return (lst);
}
