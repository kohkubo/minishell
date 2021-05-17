CC = gcc
CFLAGS = -Wall -Wextra -Werror -Ofast -I./includes
NAME = libex.a
header = libex.h

src =\
	./free_string_array.c \
	./get_next_line.c \
	./min.c \
	./free_set.c \
	./ft_xmalloc.c \
	./ft_strndup.c \
	./contain.c \
	./ft_isspace.c \

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

.PHONY: all clean fclean re init header

init:
	bash header.sh
