# ***********************************

NAME	= libex.a
CC		= gcc
CFLAGS	= -Wall -Wextra -Werror -O3 -g
obj		= $(src:%.c=%.o)

.PHONY: all clean fclean re debug sani-debug

# ***********************************

src =\
	./strsort.c \
	./free_string_array.c \
	./get_next_line.c \
	./ft_min_size_t.c \
	./free_set.c \
	./ft_xmalloc.c \
	./ft_fatal.c \
	./ft_strndup.c \
	./ft_error_exit.c \
	./ft_xcalloc.c \
	./contain.c \
	./ft_isspace.c \
	./ft_strcmp.c \
	./ft_xstrdup.c \
	./is_space_string.c \
	./spacelen.c \
	./arraylen.c \
	./print_array.c \
	./random_string.c \
	./str_arraydup.c \
	./debug_array.c \

# ***********************************

all: $(NAME)

$(NAME): $(obj)
	$(AR) -rc $(NAME) $(obj)
	ranlib $(NAME)

clean:
	$(RM) $(obj)

fclean: clean
	$(RM) $(NAME)

re: fclean all

# ***********************************

sani-debug: fclean
	$(MAKE) CFLAGS="$(CFLAGS) -fsanitize=address"
