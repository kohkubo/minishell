CC = gcc
CFLAGS = -Wall -Wextra -Werror -Ofast -I./includes
NAME = minishell
header = ./includes/shell.h
libft = ./libft/libft/libft.a #./libft/libex/libex.a

src =./srcs/main.c ./srcs/echo.c

all: $(NAME)

obj = $(src:%.c=%.o)

$(NAME): $(obj)
	$(MAKE) -C ./libft/libft
	$(CC) $(CFLAGS) $(obj) $(libft) -o $(NAME)

clean:
	$(MAKE) clean -C ./libft/libft
	@find ./tests -type f -name output -exec rm {} \;
	@find ./tests -type f -name minishell -exec rm {} \;
	@find ./tests -type f -name expect -exec rm {} \;
	$(RM) $(obj)

fclean: clean
	$(MAKE) fclean -C ./libft/libft
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re srcs header

srcs:
	$(MAKE) srcs -C ./libft
	sed -i '' -e "1,/src =/ s|src =.*|src =`find ./srcs -type f -name "*.c" | tr '\n' ' '`|" Makefile

proto = $(shell cat ./srcs/*.c | grep -e '^\(int\|void\|size_t\|t_.*\|char\|float\|double\|struct\|unsigned\|short\|const\|long\|bool\|signed\)\t' | sed -e 's/$$/;\\n/')

header:
	sed -i -e '/^\(int\|void\|size_t\|t_.*\|char\|float\|double\|struct\|unsigned\|short\|const\|long\|bool\|signed\)\t/d' $(header)
	sed -i -e "/Prototypes$$/a $(proto)" $(header)
	sed -i -e 's/^ //' $(header)

test_unit:
	bash ./tests/unit-test/test-unit.sh

test_issue:
	bash ./tests/issue/test-issue.sh
