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
		|| signal(SIGQUIT, signal_handler_prompt) == SIG_ERR)
		ft_fatal("signal error: ");
}
