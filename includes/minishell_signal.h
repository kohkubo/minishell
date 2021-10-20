#ifndef MINISHELL_SIGNAL_H
# define MINISHELL_SIGNAL_H

void	signal_init(void func1(int), void func2(int));
void	signal_handler_prompt(int sig);
void	signal_heredoc(void);
void	signal_child_process(int sig);

#endif
