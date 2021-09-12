#include "shell.h"

static void	separate_to_list(char *arg, t_list **list)
{
	char	*start;
	char	*end;

	while (*arg != '\0')
	{
		start = ft_strchr(arg, CHAR_DOL);
		if (start == NULL)
		{
			ft_lstadd_back(list, ft_lstnew(ft_xstrdup(arg)));
			break ;
		}
		if (start != arg)
			ft_lstadd_back(list, ft_xlstnew(ft_xsubstr(arg, 0, start - arg)));
		end = start + 1;
		while (ft_strchr("$", *end) == NULL)
			end++;
		ft_lstadd_back(list, ft_xlstnew(ft_xsubstr(start, 0, end - start)));
		arg = end;
	}
}

static void	expand_var(t_list *separated)
{
	char	*content;
	char	*tmp;

	while (separated)
	{
		content = (char *)separated->content;
		if (content[0] == CHAR_DOL && content[1] != '\0')
		{
			tmp = wrapper_hash_getstr(g_shell.env, content + 1);
			free_set(&separated->content, ft_xstrdup(tmp));
		}
		separated = separated->next;
	}
}

char	*minishell_expand(char *arg)
{
	t_list	*separated;
	char	*ret;

	if (arg == NULL)
		ft_fatal("minishell_expand : Invalid argument");
	if (ft_strchr(arg, CHAR_DOL) == NULL)
		return (ft_xstrdup(arg));
	separated = NULL;
	separate_to_list(arg, &separated);
	expand_var(separated);
	ret = lst_to_string(separated);
	ft_lstclear(&separated, free);
	return (ret);
}
