#include "minishell_signal.h"
#include "minishell_global.h"
#include "minishell_readline.h"
#include "libex.h"
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

void	signal_child_process(int sig)
{
	(void)sig;
	(void)sig;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
}

void	signal_handler_heredoc(int sig)
{
	(void)sig;
	g_shell.heredoc_status = 1;
}

int	rl_event_hook_heredoc(void)
{
	if (g_shell.heredoc_status == 1)
		rl_done = 1;
	return (0);
}

void	signal_init(void func1(int), void func2(int), int heredoc_hook(void))
{
	rl_event_hook = heredoc_hook;
	if (signal(SIGINT, func1) == SIG_ERR
		|| signal(SIGQUIT, func2) == SIG_ERR)
		ft_fatal("signal error: ");
}
