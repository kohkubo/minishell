#include "lex.h"
#include "shell.h"

void	lexer_handler_do(t_list **lst, char **token, t_list **ret, char *c)
{
	if (ft_isspace(*c))
		*lst = (*lst)->next;
	else if (*c == CHAR_SQUOTE || *c == CHAR_DQUOTE)
		store_quote_token(lst, token, ret);
	else if (ft_strcmp(c, LESSER2) == 0)
		store_heredoc_token(lst, token, ret);
	else if (ft_strcmp(c, PIPE2) == 0)
		ft_lstadd_back(ret, ft_lstnew(tok_new(c, CHAR_PIPE2))),
		*lst = (*lst)->next;
	else if (ft_strcmp(c, AMPERSAND2) == 0)
		ft_lstadd_back(ret, ft_lstnew(tok_new(c, CHAR_AMPERSAND2))),
		*lst = (*lst)->next;
	else if (ft_strcmp(c, GREATER2) == 0)
		ft_lstadd_back(ret, ft_lstnew(tok_new(c, CHAR_GREATER2))),
		*lst = (*lst)->next;
	else if (*c == CHAR_LESSER || *c == CHAR_GREATER || *c == CHAR_PIPE)
		ft_lstadd_back(ret, ft_lstnew(tok_new(c, *c))), *lst = (*lst)->next;
	else
		store_general_token(lst, token, ret);
}

t_state_type	lexer_handler(t_list *lst, t_lexer **lexer)
{
	t_list			*ret;
	char			*c;
	char			*token;

	ret = NULL;
	token = ft_xstrdup("");
	while (lst)
	{
		c = (char *)lst->content;
		lexer_handler_do(&lst, &token, &ret, c);
	}
	free(token), *lexer = lexer_new(ret);
	return (STATE_GENERAL);
}

void	merge_double_token(t_list **lst, char c)
{
	char	token[3];
	t_list	*next;

	if (*(char *)(*lst)->content == c && *(char *)(*lst)->next->content == c)
	{
		next = (*lst)->next->next;
		token[0] = c;
		token[1] = c;
		token[2] = '\0';
		free_set(&(*lst)->content, ft_xstrdup(token));
		free((*lst)->next->content);
		free((*lst)->next);
		(*lst)->next = next;
	}
}

void	merge_double_token_in_lst(t_list *lst)
{
	if (lst == NULL)
		ft_fatal("token_organizer : Invalid argument");
	while (lst && lst->next)
	{
		merge_double_token(&lst, CHAR_GREATER);
		merge_double_token(&lst, CHAR_LESSER);
		merge_double_token(&lst, CHAR_PIPE);
		merge_double_token(&lst, CHAR_AMPERSAND);
		lst = lst->next;
	}
}

t_state_type	minishell_lexer(char *s, t_lexer **lexer)
{
	t_list			*separated;
	t_state_type	state;

	if (s == NULL || lexer == NULL)
		ft_fatal("minishell_lexer : Invalid argument");
	if (is_space_string(s))
	{
		*lexer = lexer_new(NULL);
		return (STATE_SPACE);
	}
	separated = separate_to_lst(s, SPECIAL_CAHRS);
	merge_double_token_in_lst(separated);
	state = lexer_handler(separated, lexer);
	ft_lstclear(&separated, free);
	return (state);
}
