#ifndef MINISHELL_SIGNAL_H
# define MINISHELL_SIGNAL_H

void	signal_init(void func1(int), void func2(int), int heredoc_hook(void));
void	signal_child_process(int sig);
void	signal_handler_prompt(int sig);
void	signal_handler_heredoc(int sig);
int		rl_event_hook_heredoc(void);

#endif
