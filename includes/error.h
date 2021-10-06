#ifndef ERROR_H
# define ERROR_H

void	minishell_pexit(char *message);
int		catch_err(int status, char *title);
void	*catch_nul(void *ptr, char *title);

#endif
