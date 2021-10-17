#include "shell.h"

static t_list	*separate_to_lst(char *str, char *separator)
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

static char	*expand_env(char *content)
{
	char	*tmp;

	if (!ft_strcmp(content, "?"))
	{
		tmp = ft_itoa(g_shell.exit_status);
	}
	else
	{
		tmp = (char *)hash_getstr(g_shell.env, content);
		if (tmp == NULL)
			tmp = "";
		tmp = ft_strdup(tmp);
	}
	return (tmp);
}

void	expand_handler(t_list *lst)
{
	t_state_type	state;
	char			*content;

	state = STATE_GENERAL;
	while (lst)
	{
		content = (char *)lst->content;
		if (ft_strcmp(content, "\'") == 0 && state == STATE_GENERAL)
			free_set(&lst->content, NULL), state = STATE_IN_QUOTE;
		else if (ft_strcmp(content, "\'") == 0 && state == STATE_IN_QUOTE)
			free_set(&lst->content, NULL), state = STATE_GENERAL;
		else if (ft_strcmp(content, "\"") == 0 && state == STATE_GENERAL)
			free_set(&lst->content, NULL), state = STATE_IN_DQUOTE;
		else if (ft_strcmp(content, "\"") == 0 && state == STATE_IN_DQUOTE)
			free_set(&lst->content, NULL), state = STATE_GENERAL;
		else if (ft_strcmp(content, "$") == 0 && state != STATE_IN_QUOTE && \
			lst->next != NULL && \
ft_strchrset((char *)lst->next->content, " \t\n\v\f\r\"\'", 8) == NULL)
		{
			free_set(&lst->content, NULL), lst = lst->next;
			free_set(&lst->content, expand_env((char *)lst->content));
		}
		lst = lst->next;
	}
}

void	expand_handler_heredoc(t_list *lst)
{
	char	*content;

	while (lst)
	{
		content = (char *)lst->content;
		if (ft_strcmp(content, "$") == 0 && lst->next != NULL && \
	ft_strchrset((char *)lst->next->content, " \t\n\v\f\r", 6) == NULL)
		{
			free_set(&lst->content, NULL);
			lst = lst->next;
			free_set(&lst->content, expand_env((char *)lst->content));
		}
		lst = lst->next;
	}
}

char	*minishell_expand(char *arg, void (*handler)(t_list *))
{
	t_list	*separated;
	char	*ret;

	if (arg == NULL)
		ft_fatal("minishell_expand : Invalid argument");
	separated = separate_to_lst(arg, "\'\"\t\n\v\f\r\? $");
	handler(separated);
	ret = lst_join_str(separated, "");
	ft_lstclear(&separated, free);
	return (ret);
}
