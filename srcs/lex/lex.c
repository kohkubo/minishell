#include "lex.h"
#include "shell.h"

static t_state_type	store_quote_token(t_list **lst, char quote_type, char **token)
{
	free_set((void **)token, ft_xstrjoin(*token, (char *)(*lst)->content));
	while ((*lst)->next)
	{
		*lst = (*lst)->next;
		free_set((void **)token, ft_xstrjoin(*token, (char *)(*lst)->content));
		if (*(char *)(*lst)->content == quote_type)
		{
			*lst = (*lst)->next;
			return (STATE_GENERAL);
		}
	}
	ft_error_exit("this pattern is not supported");
	return (quote_type);
}

void	lst_spece_skip(t_list **lst)
{
	if (lst == NULL)
		ft_fatal("lst_spece_skip : Invalid argument");
	while (*lst)
	{
		if (!ft_isspace(*(char *)(*lst)->content))
			return ;
		*lst = (*lst)->next;
	}
}

t_state_type	lexer_handler(t_list *lst, t_lexer **lexer)
{
	t_list			*ret;
	char			*content;
	char			*token;

	ret = NULL;
	token = ft_xstrdup("");
	while (lst)
	{
		content = (char *)lst->content;
		if (ft_isspace(*content))
		{
			lst = lst->next;
		}
		else if (*content == CHAR_SQUOTE)
		{
			store_quote_token(&lst, CHAR_SQUOTE, &token);
			if (lst == NULL || (lst != NULL && ft_strchr(TOKEN_SEPARATOR, *(char *)lst->content) != NULL))
			{
				ft_lstadd_back(&ret, ft_lstnew(tok_new(token, TOKEN)));
				free_set((void **)&token, ft_xstrdup(""));
			}
		}
		else if (*content == CHAR_DQUOTE)
		{
			store_quote_token(&lst, CHAR_DQUOTE, &token);
			if (lst == NULL || (lst != NULL && ft_strchr(TOKEN_SEPARATOR, *(char *)lst->content) != NULL))
			{
				ft_lstadd_back(&ret, ft_lstnew(tok_new(token, TOKEN)));
				free_set((void **)&token, ft_xstrdup(""));
			}
		}
		else if (*content == CHAR_LESSER 
				&& lst->next != NULL 
				&& ft_strcmp(lst->next->content, LESSER_TOKEN) == 0)
		{
			ft_lstadd_back(&ret, ft_lstnew(tok_new(LESSER2_TOKEN, CHAR_LESSER2)));
			lst = lst->next->next;
			lst_spece_skip(&lst);
			if (lst == NULL)
				break ;
			free_set((void **)&token, heredoc_readline(lst->content));
			ft_lstadd_back(&ret, ft_lstnew(tok_new(token, TOKEN)));
			free_set((void **)&token, ft_xstrdup(""));
			lst = lst->next;
		}
		else if (*content == CHAR_LESSER)
		{
			ft_lstadd_back(&ret, ft_lstnew(tok_new(LESSER_TOKEN, CHAR_LESSER)));
			lst = lst->next;
		}
		else if (*content == CHAR_GREATER 
				&& lst->next != NULL 
				&& ft_strcmp(lst->next->content, GREATER_TOKEN) == 0)
		{
			ft_lstadd_back(&ret, ft_lstnew(tok_new(GREATER2_TOKEN, CHAR_GREATER2)));
			lst = lst->next->next;
		}
		else if (*content == CHAR_GREATER)
		{
			ft_lstadd_back(&ret, ft_lstnew(tok_new(GREATER_TOKEN, CHAR_GREATER)));
			lst = lst->next;
		}
		else if (*content == CHAR_PIPE)
		{
			ft_lstadd_back(&ret, ft_lstnew(tok_new(PIPE_TOKEN, CHAR_PIPE)));
			lst = lst->next;
		}
		else
		{
			free_set((void **)&token, ft_xstrjoin(token, content));
			lst = lst->next;
			if (lst == NULL || (lst != NULL && ft_strchr(TOKEN_SEPARATOR, *(char *)lst->content) != NULL))
			{
				ft_lstadd_back(&ret, ft_lstnew(tok_new(token, TOKEN)));
				free_set((void **)&token, ft_xstrdup(""));
			}
		}
	}
	free(token);
	*lexer = lexer_new(ret);
	return (STATE_GENERAL);
}

t_state_type	minishell_lexer(char *s, t_lexer **lexer)
{
	t_list			*separated;
	t_state_type	state;

	if (s == NULL || lexer == NULL)
		ft_fatal("minishell_lexer : Invalid argument");
	separated = separate_to_lst(s, "\'\"\t\n\v\f\r <>|");
	state = lexer_handler(separated, lexer);
	ft_lstclear(&separated, free);
	return (state);
}
