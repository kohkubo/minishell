CC = gcc
CFLAGS = -Wall -Wextra -Werror -Ofast -I./includes
NAME = minishell
header = ./includes/shell.h
libft = ./libft/libft/libft.a ./libft/libex/libex.a

src =./srcs/main.c\
./srcs/parse/parse.c\
./srcs/built-in/ft_exit.c\

all: $(NAME)

obj = $(src:%.c=%.o)

$(NAME): $(obj)
	$(MAKE) -C ./libft
	$(CC) $(CFLAGS) $(obj) $(libft) -o $(NAME)

clean:
	$(MAKE) clean -C ./libft
	@find ./tests -type f -name output -exec rm {} \;
	@find ./tests -type f -name minishell -exec rm {} \;
	@find ./tests -type f -name expect -exec rm {} \;
	$(RM) $(obj)

fclean: clean
	$(MAKE) fclean -C ./libft
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re srcs header test test_issue test_unit

srcs:
	sed -i '' -e "1,/src =/ s|src =.*|src =`find ./srcs -type f -name "*.c" | tr '\n' ' '`|" Makefile

header:
	bash header.sh
	bash libft/libft/header.sh
	bash libft/libex/header.sh

test:
	bash ./all-test.sh

test_unit:
	bash ./tests/unit-test/test-units.sh

test_issue:
	bash ./tests/issue/test-issues.sh
