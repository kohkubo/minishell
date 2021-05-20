CC = gcc
CFLAGS = -Wall -Wextra -Werror -O3
NAME = libex.a

src =\
	./free_string_array.c \
	./get_next_line.c \
	./min.c \
	./free_set.c \
	./errlst.c \
	./ft_xmalloc.c \
	./ft_strerror.c \
	./ft_strndup.c \
	./contain.c \
	./ft_isspace.c \

.PHONY: all clean fclean re init header debug sani-debug

all: $(NAME)

obj = $(src:%.c=%.o)

$(NAME): $(obj)
	$(AR) -rc $(NAME) $(obj)
	ranlib $(NAME)

clean:
	$(RM) $(obj)

fclean: clean
	$(RM) $(NAME)

re: fclean all

init:
	bash header.sh

debug: fclean
	$(MAKE) CFLAGS="$(CFLAGS) -D DEBUG=1 -g"
	$(MAKE) clean

sani-debug: fclean
	$(MAKE) CFLAGS="$(CFLAGS) -D DEBUG=1 -g -fsanitize=address"
	$(MAKE) clean
