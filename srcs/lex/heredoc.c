#include "lex.h"
#include "shell.h"

char	*heredoc_readline(char *heredoc, char *tok)
{
	char	*read;
	int		flg;

	flg = 0;
	while (1)
	{
		read = readline(HEREDOC_PROMPT);
		if (ft_strcmp(read, heredoc) == 0)
		{
			free_set((void **)&read, NULL);
			return (tok);
		}
		free_set((void **)&tok, ft_xstrjoin(tok, read));
		free_set((void **)&tok, ft_xstrjoin(tok, "\n"));
		free_set((void **)&read, NULL);
		flg++;
	}
}

char	*generate_heredoc(char *s)
{
	char	*buf;
	int		i;

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

	if (*(*s + 2) == 0 || is_space_string(*s + 2))
	{
		ft_error_exit(\
			"minishell : syntax error near unexpected token `newline'");
	}
	token_store2_and_create(*l, tok, s);
	*s += 1;
	*i = 0;
	*s += spacelen(*s);
	heredoc = generate_heredoc(*s);
	(*tok)->data = heredoc_readline(heredoc, (*tok)->data);
	(*tok)->type = TOKEN;
	*s += ft_strlen(heredoc);
	*s += spacelen(*s);
	free_set((void **)&heredoc, NULL);
	token_end_and_create(*l, tok, *s, NULL);
	return (STATE_GENERAL);
}
