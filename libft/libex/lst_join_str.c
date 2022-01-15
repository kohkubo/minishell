#include "libex.h"

char	*lst_join_str(t_list *lst, char *sep)
{
	char	*str;

	if (lst == NULL)
		ft_fatal("lst_join_str: Invalid argument");
	if (sep == NULL)
		sep = "";
	if ((char *)lst->content != NULL)
		str = ft_xstrdup((char *)lst->content);
	else
		str = ft_xstrdup("");
	while (lst->next)
	{
		free_set(&str, ft_xstrjoin(str, sep));
		if ((char *)lst->next->content != NULL)
			free_set(&str,
				ft_xstrjoin(str, (char *)lst->next->content));
		lst = lst->next;
	}
	return (str);
}
