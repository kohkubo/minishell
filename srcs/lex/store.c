#include "lex.h"

static void	lst_chrset_skip(t_list **lst, char *chrset)
{
	if (lst == NULL || chrset == NULL)
		ft_fatal("lst_spece_skip : Invalid argument");
	while (*lst)
	{
		if (ft_strchr(chrset, *(char *)(*lst)->content) == NULL)
			return ;
		*lst = (*lst)->next;
	}
}

t_state_type	store_quote_token(t_list **lst, char **token, t_list **ret)
{
	char	quote_type;

	quote_type = *(char *)(*lst)->content;
	free_set((void **)token, ft_xstrjoin(*token, (char *)(*lst)->content));
	while (1)
	{
		*lst = (*lst)->next;
		if (*lst == NULL)
			ft_error_exit("this pattern is not supported");
		free_set((void **)token, ft_xstrjoin(*token, (char *)(*lst)->content));
		if (*(char *)(*lst)->content == quote_type)
		{
			*lst = (*lst)->next;
			break ;
		}
	}
	if (*lst == NULL || \
	(*lst != NULL && ft_strchr(SEPARATOR, *(char *)(*lst)->content) != NULL))
	{
		ft_lstadd_back(ret, ft_lstnew(tok_new(*token, TOKEN)));
		free_set((void **)token, ft_xstrdup(""));
	}
	return (STATE_GENERAL);
}

void	store_general_token(t_list **lst, char **token, t_list **ret)
{
	free_set((void **)token, ft_xstrjoin(*token, (char *)(*lst)->content));
	*lst = (*lst)->next;
	if (*lst == NULL || \
	(*lst != NULL && ft_strchr(SEPARATOR, *(char *)(*lst)->content) != NULL))
	{
		ft_lstadd_back(ret, ft_lstnew(tok_new(*token, TOKEN)));
		free_set((void **)token, ft_xstrdup(""));
	}
}

t_state_type	store_heredoc_token(t_list **lst, char **token, t_list **ret)
{
	ft_lstadd_back(ret, ft_lstnew(tok_new(LESSER2, CHAR_LESSER2)));
	*lst = (*lst)->next;
	lst_chrset_skip(lst, TOKEN_WSPACE_QUOTES);
	if (*lst == NULL)
		return (STATE_ERROR);
	free_set((void **)token, heredoc_readline((*lst)->content));
	ft_lstadd_back(ret, ft_lstnew(tok_new(*token, TOKEN)));
	free_set((void **)token, ft_xstrdup(""));
	*lst = (*lst)->next;
	return (STATE_GENERAL);
}
