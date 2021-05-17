NAME = libft.a

all: $(NAME)

$(NAME):
	$(MAKE) -C ./libft
	$(MAKE) -C ./libex

clean:
	$(MAKE) clean -C ./libft
	$(MAKE) clean -C ./libex

fclean: clean
	$(MAKE) fclean -C ./libft
	$(MAKE) fclean -C ./libex
	$(RM) $(NAME)

init:
	$(MAKE) init -C ./libft
	$(MAKE) init -C ./libex

re: fclean all

.PHONY: all clean fclean re srcs
