#include "shell.h"

static t_list	*separate_to_lst(char *str, char *separator)
{
	t_list	*list;
	char	*start;

	list = NULL;
	while (*str != '\0')
	{
		if (ft_strchr(separator, *str) != NULL)
		{
			ft_lstadd_back(&list, ft_lstnew(ft_xsubstr(str, 0, 1)));
			str++;
		}
		else
		{
			start = str;
			while (ft_strchr(separator, *str) == NULL)
				str++;
			ft_lstadd_back(&list, ft_lstnew(ft_xsubstr(start, 0, str - start)));
		}
	}
	return (list);
}

static t_list	*expand_dol(t_list *separated)
{
	char	*content;
	char	*tmp;

	if (separated->next == NULL || \
ft_strchrset((char *)separated->next->content, " \t\n\v\f\r\"\'", 8) != NULL)
		free_set(&separated->content, ft_xstrdup("$"));
	else
	{
		free_set(&separated->content, NULL);
		separated = separated->next;
		content = (char *)separated->content;
		tmp = (char *)hash_getstr(g_shell.env, content);
		if (tmp == NULL)
			tmp = "";
		free_set(&separated->content, ft_xstrdup(tmp));
	}
	return (separated);
}

static void	expand_handler(t_list *separated)
{
	t_state_type	state;
	char			*content;

	state = STATE_GENERAL;
	while (separated)
	{
		content = (char *)separated->content;
		if (ft_strcmp(content, "\'") == 0 && state == STATE_GENERAL)
			free_set(&separated->content, NULL), state = STATE_IN_QUOTE;
		else if (ft_strcmp(content, "\'") == 0 && state == STATE_IN_QUOTE)
			free_set(&separated->content, NULL), state = STATE_GENERAL;
		else if (ft_strcmp(content, "\"") == 0 && state == STATE_GENERAL)
			free_set(&separated->content, NULL), state = STATE_IN_DQUOTE;
		else if (ft_strcmp(content, "\"") == 0 && state == STATE_IN_DQUOTE)
			free_set(&separated->content, NULL), state = STATE_GENERAL;
		else if (ft_strcmp(content, "$") == 0 && state != STATE_IN_QUOTE)
			separated = expand_dol(separated);
		separated = separated->next;
	}
}

char	*minishell_expand(char *arg)
{
	t_list	*separated;
	char	*ret;

	if (arg == NULL)
		ft_fatal("minishell_expand : Invalid argument");
	separated = separate_to_lst(arg, "\'\"\t\n\v\f\r $");
	expand_handler(separated);
	ret = lst_join_str(separated, "");
	ft_lstclear(&separated, free);
	return (ret);
}
