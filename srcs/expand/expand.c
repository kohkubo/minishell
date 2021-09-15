#include "shell.h"

#include "logging.h"
#include "lex.h"

static void	pick(t_list **list, t_token_type type, char *start, char *end);

static t_list	*separate_to_list(char *word, t_state_type type)
{
	t_list	*list;
	char	*find;
	char	*end;

	list = NULL;
	while (*word != '\0')
	{
		if (type == STATE_IN_DQUOTE)
			find = ft_strchrset(word, "$\0", 2);
		else
			find = ft_strchrset(word, "$\'\"\0", 4);
		if (word != find)
			pick(&list, CHAR_GENERAL, word, find);
		if (*find == '\0')
			break ;
		else if (*find == '$')
			end = ft_strchrset(find + 1, "\t\n\v\f\r \"\'$\0", 10) - 1;
		else if (*find == '\"' || *find == '\'')
			end = ft_strchr(find + 1, *find);
		pick(&list, *find, find, end);
		word = end + 1;
	}
	return (list);
}

static void	pick(t_list **list, t_token_type type, char *start, char *end)
{
	char	*in_quote_str;

	if (type == CHAR_DQUOTE)
	{
		in_quote_str = ft_xsubstr(start, 1, end - start - 1);
		ft_lstadd_back(list, separate_to_list(in_quote_str, STATE_IN_DQUOTE));
		free(in_quote_str);
	}
	else if (type == CHAR_DOLLAR)
		ft_lstadd_back(list, ft_xlstnew(
				new_tok(CHAR_DOLLAR, ft_xsubstr(start, 1, end - start))));
	else if (type == CHAR_QUOTE)
		ft_lstadd_back(list, ft_xlstnew(
				new_tok(CHAR_GENERAL, ft_xsubstr(start, 1, end - start - 1))));
	else
		ft_lstadd_back(list, ft_xlstnew(
				new_tok(type, ft_xsubstr(start, 0, end - start))));
}

static void	*expand_for_map(void *content)
{
	t_tok	*tok;
	char	*new_str;

	tok = (t_tok *)content;
	if (tok->type == CHAR_DOLLAR)
	{
		new_str = (char *)hash_getstr(g_shell.env, tok->data);
		if (new_str == NULL)
			new_str = "";
		if (ft_strcmp(tok->data, "") == 0)
			new_str = "$";
		return (ft_xstrdup(new_str));
	}
	return (ft_xstrdup(tok->data));
}

// void	print(void *content)
// {
// 	ft_putstr_fd(YELLOW, 2);
// 	ft_putendl_fd(((t_tok *)content)->data, 2);
// 	ft_putstr_fd(END, 2);
// }

char	*minishell_expand(char *word)
{
	t_list	*separated;
	t_list	*expanded;
	char	*ret;

	if (word == NULL)
		ft_fatal("minishell_expand : Invalid argument");
	separated = separate_to_list(word, 0);
	expanded = ft_lstmap(separated, expand_for_map, free);
	ret = lst_join_str(expanded, "");
	ft_lstclear(&separated, tok_free);
	ft_lstclear(&expanded, free);
	return (ret);
}
