CC = gcc
CFLAGS = -Wall -Wextra -Werror -O3
NAME = libex.a

src =\
	./hash_contains_key.c \
	./strsort.c \
	./hasher.c \
	./hash_remove.c \
	./hash_getkeys.c \
	./hash_display_table.c \
	./free_string_array.c \
	./hash_setstr.c \
	./hash_getstr.c \
	./get_next_line.c \
	./min.c \
	./free_set.c \
	./errlst.c \
	./hash_search.c \
	./ft_xmalloc.c \
	./ft_fatal.c \
	./ft_strerror.c \
	./ft_strndup.c \
	./hash_clear_dict_item.c \
	./hash_getall.c \
	./hash_setint.c \
	./hash_clear_hash_table.c \
	./hash_getint.c \
	./contain.c \
	./ft_isspace.c \
	./hash_create_table.c \
	./ft_strcmp.c \

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

sani-debug: fclean
	$(MAKE) CFLAGS="$(CFLAGS) -D DEBUG=1 -g -fsanitize=address"
