#include "shell.h"

static char	*expand_env(t_list *separated)
{
	char	*tmp;

	tmp = (char *)hash_getstr(g_shell.env, (char *)separated->content);
	if (tmp == NULL)
		tmp = "";
	return (ft_xstrdup(tmp));
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
		else if (ft_strcmp(content, "$") == 0 && state != STATE_IN_QUOTE
			&& separated->next != NULL && \
	ft_strchrset((char *)separated->next->content, " \t\n\v\f\r\"\'") == NULL)
		{
			free_set(&separated->content, NULL);
			separated = separated->next;
			free_set(&separated->content, expand_env(separated));
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
	separated = separate_to_list(arg, "\'\"\t\n\v\f\r $");
	expand_handler(separated);
	ret = lst_to_string(separated);
	ft_lstclear(&separated, free);
	return (ret);
}
