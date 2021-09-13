#include "shell.h"

static char	*expand_env(char *arg)
{
	t_list	*list;
	t_list	*head;
	char	*tmp;

	list = separate_to_list(arg, "$ \t\n\v\f\r");
	head = list;
	while (list)
	{
		if (ft_strcmp((char *)list->content, "$") == 0 && list->next != NULL
			&& ft_strchrset((char *)list->next->content, " \t\n\v\f\r") == NULL)
		{
			free_set(&list->content, NULL);
			list = list->next;
			tmp = (char *)hash_getstr(g_shell.env, (char *)list->content);
			if (tmp == NULL)
				tmp = "";
			free_set(&list->content, ft_xstrdup(tmp));
		}
		list = list->next;
	}
	tmp = lst_to_string(head);
	ft_lstclear(&head, free);
	return (tmp);
}

static void	expand_quote(t_list *separated)
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
		else if (ft_strchr(content, CHAR_DOL) != NULL
			&& state != STATE_IN_QUOTE)
			free_set(&separated->content, expand_env(content));
		separated = separated->next;
	}
}

char	*minishell_expand(char *arg)
{
	t_list	*separated;
	char	*ret;

	if (arg == NULL)
		ft_fatal("minishell_expand : Invalid argument");
	separated = separate_to_list(arg, "\'\"\t\n\v\f\r");
	expand_quote(separated);
	ret = lst_to_string(separated);
	ft_lstclear(&separated, free);
	return (ret);
}
