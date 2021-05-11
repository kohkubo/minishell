CC = gcc
CFLAGS = -Wall -Wextra -Werror -Ofast
NAME = libft.a
header = libft.h

src =./ft_strncmp.c

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

.PHONY: all clean fclean re srcs header

srcs:
	sed -i '' -e "1,/src =/ s|src =.*|src =`find . -type f -name "*.c" | tr '\n' ' '`|" Makefile

proto = $(shell cat ./srcs/*.c | grep -e '^\(int\|void\|size_t\|t_.*\|char\|float\|double\|struct\|unsigned\|short\|const\|long\|bool\|signed\)\t' | sed -e 's/$$/;\\n/')

header:
	sed -i -e '/^\(int\|void\|size_t\|t_.*\|char\|float\|double\|struct\|unsigned\|short\|const\|long\|bool\|signed\)\t/d' $(header)
	sed -i -e "/Prototypes$$/a$(proto)" $(header)
	sed -i -e 's/^ //' $(header)
