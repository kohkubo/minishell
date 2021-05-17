CC = gcc
CFLAGS = -Wall -Wextra -Werror -O3 -I$(includes)
NAME = minishell
includes = ./includes
libft = ./libft/libft/libft.a ./libft/libex/libex.a

src =\
	./srcs/parse/parse.c \
	./srcs/built-in/ft_exit.c \
	./srcs/main.c \

.PHONY: all clean fclean re init test test_issue test_unit header debug sani-debug prepush

all: $(NAME)

obj = $(src:%.c=%.o)

$(NAME): $(obj)
	$(MAKE) -C ./libft/libft
	$(MAKE) -C ./libft/libex
	$(CC) $(CFLAGS) $(obj) $(libft) -o $(NAME)

clean:
	$(MAKE) clean -C ./libft/libft
	$(MAKE) clean -C ./libft/libex
	@find ./tests -type f -name output -exec rm {} \;
	@find ./tests -type f -name minishell -exec rm {} \;
	@find ./tests -type f -name expect -exec rm {} \;
	$(RM) $(obj)

fclean: clean
	$(MAKE) fclean -C ./libft/libft
	$(MAKE) fclean -C ./libft/libex
	$(RM) $(NAME)

re: fclean all

init:
	$(MAKE) init -C ./libft/libft
	$(MAKE) init -C ./libft/libex
	zsh header.sh

test:
	bash ./all-test.sh

test_unit:
	bash ./tests/unit-test/test-units.sh

test_issue:
	bash ./tests/issue/test-issues.sh

debug: fclean
	$(MAKE) re -C ./libft/libft
	$(MAKE) debug -C ./libft/libex
	$(MAKE) CFLAGS="$(CFLAGS) -D DEBUG=1 -g"
	$(MAKE) clean

sani-debug: fclean
	$(MAKE) re -C ./libft/libft
	$(MAKE) debug -C ./libft/libex
	$(MAKE) CFLAGS="$(CFLAGS) -D DEBUG=1 -g -fsanitize=address"
	$(MAKE) clean

norm:
	norminette ./srcs ./includes ./libft

prepush: norm test 
