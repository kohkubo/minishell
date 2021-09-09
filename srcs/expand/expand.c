#include "shell.h"

// TODO: ft_lstnewのcatch_null
static void	separate_to_list(char *arg, t_list **list)
{
	char	*start;
	char	*end;

	while (*arg != '\0')
	{
		start = ft_strchr(arg, '$');
		if (start == NULL)
		{
			ft_lstadd_back(list, ft_lstnew(ft_xstrdup(arg)));
			break ;
		}
		if (start != arg)
			ft_lstadd_back(list, ft_lstnew(ft_xsubstr(arg, 0, start - arg)));
		end = start + 1;
		while (ft_strchr("$ \"\'\0", *end) == NULL)
			end++;
		ft_lstadd_back(list, ft_lstnew(ft_xsubstr(start, 0, end - start)));
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
		if (content[0] == '$' && content[1] != '\0')
		{
			tmp = (char *)hash_getstr(g_shell.env, content + 1);
			if (tmp == NULL)
				tmp = "";
			free_set(&separated->content, ft_xstrdup(tmp));
		}
		separated = separated->next;
	}
}

static char	*join(t_list *separated)
{
	char	*tmp;

	tmp = ft_xstrdup("");
	while (separated)
	{
		free_set((void **)&tmp, ft_xstrjoin(tmp, separated->content));
		separated = separated->next;
	}
	return (tmp);
}

char	*minishell_expand(char *arg)
{
	t_list	*separated;
	char	*ret;

	if (arg == NULL)
		ft_fatal("minishell_expand : Invalid argument");
	if (ft_strchr(arg, '$') == NULL)
		return (ft_xstrdup(arg));
	separated = NULL;
	separate_to_list(arg, &separated);
	expand_var(separated);
	ret = join(separated);
	ft_lstclear(&separated, free);
	return (ret);
}
