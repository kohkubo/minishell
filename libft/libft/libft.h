#ifndef LIBFT_H
# define LIBFT_H
# include <stdlib.h>
# include <unistd.h>
# include <stdint.h>
# include <limits.h>
# include <errno.h>
# include "../libex/libex.h"

typedef	struct	s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;

# ifndef T_BOOL_H
#  define T_BOOL_H
typedef enum	e_bool
{
	FALSE,
	TRUE
}				t_bool;
# endif

// Prototype


#endif
