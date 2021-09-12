#include "shell.h"

static void	separate_to_list(char *arg, t_list **list)
{
	char	*buf;
	int		i;

	buf = ft_xmalloc(sizeof(char) * (ft_strlen(arg) + 1));
	while (*arg != '\0')
	{
		if (*arg == CHAR_DOL || *arg == CHAR_QUOTE
			|| *arg == CHAR_DQUOTE || *arg == CHAR_SPACE)
		{
			ft_lstadd_back(list, ft_lstnew(ft_xsubstr(arg, 0, 1)));
			arg++;
		}
		else
		{
			i = 0;
			while (*arg != '\0'
				&& *arg != CHAR_DOL && *arg != CHAR_QUOTE
				&& *arg != CHAR_DQUOTE && *arg != CHAR_SPACE)
				buf[i++] = *arg++;
			buf[i] = '\0';
			ft_lstadd_back(list, ft_lstnew(ft_xstrdup(buf)));
		}
	}
	free(buf);
}

static t_list	*expand_env(t_list *separated)
{
	char	*content;
	char	*tmp;

	if (separated->next == NULL
		|| ft_isspace(((char *)separated->next->content)[0]))
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

static void	expand_var(t_list *separated)
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
	separated = NULL;
	separate_to_list(arg, &separated);
	expand_var(separated);
	ret = lst_to_string(separated);
	ft_lstclear(&separated, free);
	return (ret);
}
