#ifndef ERROR_H
# define ERROR_H

void			pexit(char *message, int status);
int				catch_error(int status, char *title);
void			*catch_null(void *ptr, char *title);

#endif
