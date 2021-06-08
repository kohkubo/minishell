# ***********************************

NAME	= libex.a
CC		= gcc
CFLAGS	= -Wall -Wextra -Werror -O3
obj		= $(src:%.c=%.o)

.PHONY: all clean fclean re debug sani-debug

# ***********************************

src =\
	./strsort.c \
	./free_string_array.c \
	./get_next_line.c \
	./min.c \
	./free_set.c \
	./errlst.c \
	./ft_xmalloc.c \
	./ft_fatal.c \
	./ft_strerror.c \
	./ft_strndup.c \
	./contain.c \
	./ft_isspace.c \
	./ft_strcmp.c \
	./ft_xstrdup.c \

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

debug: fclean
	$(MAKE) CFLAGS="$(CFLAGS) -D DEBUG=1 -g"

sani-debug: fclean
	$(MAKE) CFLAGS="$(CFLAGS) -D DEBUG=1 -g -fsanitize=address"
