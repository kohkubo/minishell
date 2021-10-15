#include "lex.h"
#include "shell.h"

char	*heredoc_readline(char *heredoc, char *tok)
{
	char	*read;
	int		flg;

	flg = 0;
	signal_heredoc();
	while (1)
	{
		read = readline(HEREDOC_PROMPT);
		if (g_shell.heredoc_status == 1 || read == NULL)
		{
			free_set((void **)&tok, ft_strdup(""));
			break ;
		}
		if (ft_strcmp(read, heredoc) == 0)
			break ;
		free_set((void **)&tok, ft_xstrjoin(tok, read));
		free_set((void **)&tok, ft_xstrjoin(tok, "\n"));
		free_set((void **)&read, NULL);
		flg++;
	}
	free_set((void **)&read, NULL);
	g_shell.heredoc_status = 0;
	signal_init();
	return (tok);
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
		ft_putendl_fd(\
			"minishell : syntax error near unexpected token `newline'", 2);
		g_shell.exit_status = 1;
		token_end(*l, tok, 0);
		return (STATE_ERROR);
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
