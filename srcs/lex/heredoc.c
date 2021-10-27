#include "lex.h"
#include "shell.h"

char	*heredoc_readline(char *heredoc)
{
	char	*read;
	int		flg;
	char	*tok;

	flg = 0;
	tok = ft_xstrdup("");
	signal_init(signal_handler_heredoc, SIG_IGN, rl_event_hook_heredoc);
	while (1)
	{
		read = readline(HEREDOC_PROMPT);
		if (g_shell.heredoc_status == 1 || read == NULL)
		{
			free_set((void **)&tok, ft_xstrdup(""));
			break ;
		}
		if (ft_strcmp(read, heredoc) == 0)
			break ;
		free_set((void **)&tok, ft_xstrjoin(tok, read));
		free_set((void **)&tok, ft_xstrjoin(tok, "\n")), free(read);
		flg++;
	}
	free_set((void **)&read, NULL);
	g_shell.heredoc_status = 0;
	signal_init(signal_handler_prompt, SIG_IGN, NULL);
	return (tok);
}
