/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kohkubo <kohkubo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 16:06:41 by kohkubo           #+#    #+#             */
/*   Updated: 2021/08/09 16:06:41 by kohkubo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"
#include "shell.h"

char	*heredoc_readline(char *heredoc, char *tok)
{
	char	*tmp;
	int		flg;

	flg = 0;
	while (1)
	{
		tmp = readline(HEREDOC_PROMPT);
		if (ft_strcmp(tmp, heredoc) == 0)
		{
			free_set((void **)&tmp, NULL);
			return (tok);
		}
		if (flg++ > 0)
			free_set((void **)&tok, ft_strjoin(tok, "\n"));
		free_set((void **)&tok, ft_strjoin(tok, tmp));
		free_set((void **)&tmp, NULL);
	}
}

char	*generate_heredoc(char *s)
{
	char	*buf;
	int		i;

	while (ft_isspace(*s))
		s++;
	buf = ft_xcalloc(1, ft_strlen(s) + 1);
	i = 0;
	while (s[i])
	{
		if (ft_isspace(s[i]))
			break ;
		buf[i] = s[i];
		i++;
	}
	free_set((void **)&buf, ft_xstrdup(buf));
	return (buf);
}

t_state_type	heredoc(t_lexer **l, t_tok **tok, char **s, size_t *i)
{
	char	*heredoc;
	int		len;

	if (*(*s + 2) == 0 || is_space_string(*s + 2))
	{
		ft_error_exit(\
			"minishell : syntax error near unexpected token `newline'");
	}
	token_store2_and_create(*l, tok, s);
	*s += 1;
	heredoc = generate_heredoc(*s);
	(*tok)->data = heredoc_readline(heredoc, (*tok)->data);
	(*tok)->type = TOKEN;
	len = ft_strlen(heredoc);
	*s += len;
	*i += len;
	free_set((void **)&heredoc, NULL);
	while (ft_isspace(**s))
	{
		*s += 1;
		*i += 1;
	}
	token_end_and_create(*l, tok, *s, i);
	return (STATE_GENERAL);
}
