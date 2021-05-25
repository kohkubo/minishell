# ***********************************

NAME	= libhash.a
CC		= gcc
CFLAGS	= -Wall -Wextra -Werror -O3
obj		= $(src:%.c=%.o)

.PHONY: all clean fclean re debug sani-debug

# ***********************************

src =\
	./hash_contains_key.c \
	./hasher.c \
	./hash_remove.c \
	./hash_getkeys.c \
	./hash_setstr.c \
	./hash_getstr.c \
	./hash_search.c \
	./hash_clear_dict_item.c \
	./hash_getall.c \
	./hash_setint.c \
	./hash_clear_hash_table.c \
	./hash_getint.c \
	./hash_create_table.c \

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
