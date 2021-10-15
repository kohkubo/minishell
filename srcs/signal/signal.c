#include "shell.h"
#include <signal.h>
#include <string.h>

void	signal_handler_prompt(int sig)
{
	(void)sig;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	signal_init(void)
{
	if (signal(SIGINT, signal_handler_prompt) == SIG_ERR
		|| signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		ft_fatal("signal error: ");
	rl_event_hook = NULL;
}

void	signal_handler_exit(int sig)
{
	(void)sig;
	g_shell.heredoc_status = 1;
}

static int	rl_event_hook_heredoc(void)
{
	if (g_shell.heredoc_status == 1)
		rl_done = 1;
	return (0);
}

void	signal_heredoc(void)
{
	rl_event_hook = rl_event_hook_heredoc;
	if (signal(SIGINT, signal_handler_exit) == SIG_ERR
		|| signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		ft_fatal("signal error: ");
}
