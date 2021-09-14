#include "shell.h"

static t_list	*expand_env(t_list *separated)
{
	char	*content;
	char	*tmp;

	if (separated->next == NULL || \
	ft_strchrset((char *)separated->next->content, " \t\n\v\f\r\"\'") != NULL)
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

static void	minishell_expand_do(t_list *separated)
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
			separated = expand_env(separated);
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
	minishell_expand_do(separated);
	ret = lst_to_string(separated);
	ft_lstclear(&separated, free);
	return (ret);
}
