#include "shell.h"

static void	*expand(void *content)
{
	char	*tmp;
	t_tok	*tok;

	tok = (t_tok *)content;
	if (tok->type == CHAR_ENV)
	{
		tmp = (char *)hash_getstr(g_shell.env, tok->data);
		if (tmp == NULL)
			tmp = "";
		return (ft_xstrdup(tmp));
	}
	else if (tok->type == CHAR_DOL)
		return (NULL);
	else if (tok->type == CHAR_DQUOTE)
		return (NULL);
	else if (tok->type == CHAR_QUOTE)
		return (NULL);
	return (ft_xstrdup(tok->data));
}

void	*expand_iter(void *content)
{
	char	*tmp;
	t_tok	*tok;

	tok = (t_tok *)content;
	if (tok->type == CHAR_DOL)
	{
		tmp = (char *)hash_getstr(g_shell.env, tok->data);
		if (tmp == NULL)
			tmp = "";
		return (ft_xstrdup(tmp));
	}
	else if (tok->type == CHAR_DQUOTE)
		return (NULL);
	else if (tok->type == CHAR_QUOTE)
		return (NULL);
	return (ft_xstrdup(tok->data));
}


void	token_state_lst(t_list *separated_str)
{
	t_state_type	state;
	char			*content;

	while (separated_str)
	{
		content = (char *)separated_str->content;
		if (ft_strcmp(content, "'") == 0 && state == STATE_GENERAL)
		{
			state = STATE_IN_QUOTE;
			free_set(&separated_str->content, new_tok(CHAR_QUOTE, ft_xstrdup(content)));
		}
		else if (ft_strcmp(content, "'") == 0 && state == STATE_IN_QUOTE)
		{
			state = STATE_GENERAL;
			free_set(&separated_str->content, new_tok(CHAR_QUOTE, ft_xstrdup(content)));
		}
		else if (ft_strcmp(content, "\"") == 0 && state == STATE_GENERAL)
		{
			state = STATE_IN_DQUOTE;
			free_set(&separated_str->content, new_tok(CHAR_DQUOTE, ft_xstrdup(content)));
		}
		else if (ft_strcmp(content, "\"") == 0 && state == STATE_IN_DQUOTE)
		{
			state = STATE_GENERAL;
			free_set(&separated_str->content, new_tok(CHAR_DQUOTE, ft_xstrdup(content)));
		}
		else if (ft_strcmp(content, "$") == 0 && state != STATE_IN_QUOTE)
		{
			if (separated_str->next == NULL || ft_strchrset((char *)separated_str->next->content, "\'\"\t\n\v\f\r ") != NULL)
				free_set(&separated_str->content, new_tok(CHAR_GENERAL, ft_xstrdup(content)));
			else
			{
				free_set(&separated_str->content, new_tok(CHAR_DOL, ft_xstrdup(content)));
				separated_str = separated_str->next;
				free_set(&separated_str->content, new_tok(CHAR_ENV, ft_xstrdup((char *)separated_str->content)));
			}
		}
		else
			free_set(&separated_str->content, new_tok(CHAR_GENERAL, ft_xstrdup(content)));
		separated_str = separated_str->next;
	}
}

void	print_list(t_list *lst)
{
	while (lst)
	{
		ft_putendl_fd(((char *)lst->content), 1);
		lst = lst->next;
	}
}

void print_list_tok(t_list *lst)
{
	while (lst)
	{
		if (lst->content != NULL)
		{
			t_tok *tok = (t_tok *)lst->content;
			printf("%s\n", tok->data);
			printf("%d\n", tok->type);
		}
		lst = lst->next;
	}
}

char	*minishell_expand(char *arg)
{
	t_list	*separated;
	t_list	*expanded_strlst;
	char	*ret;

	if (arg == NULL)
		ft_fatal("minishell_expand : Invalid argument");
	separated = separate_to_list(arg, "\'\"\t\n\v\f\r $");
	token_state_lst(separated);
	expanded_strlst = ft_lstmap(separated, expand, tok_free);
	ret = lst_to_string(expanded_strlst);
	ft_lstclear(&separated, tok_free);
	ft_lstclear(&expanded_strlst, free);
	return (ret);
}
