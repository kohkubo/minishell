# ***********************************

.PHONY		: all clean fclean re \
			init \
			norm \
			prepush \
			test \
			test_issue \
			test_unit \
			leak \
			debug \
			sani-debug \
			get_module \
			FORCE \

# ***********************************

NAME		= minishell
includes	= ./includes ./libft/libft ./libft/libex ./libft/libhash
src_dir		= srcs
obj_dir		= objs
obj			= $(src:%.c=$(src_dir)/%.o)

# ***********************************

CC 			= gcc
LIBS		= -L./libft/libft -L./libft/libex -L./libft/libhash -lft -lex -lhash -lreadline
CFLAGS		= -Wall -Wextra -Werror -O3 -g $(includes:%=-I%)

# ***********************************

src =\
	./lex/lex.c \
	./lex/token.c \
	./lex/heredoc.c \
	./lex/data.c \
	./parse/parse.c \
	./built-in/ft_exit.c \
	./built-in/echo.c \
	./main.c \
	./env/env.c \

# ***********************************

lib_dir		= libft
lib			= $(libft) \
			$(libex) \
			$(libhash) \

sharedlib	= ./tests/sharedlib.c

# ****************

libft_dir	= $(lib_dir)/libft
libft		= $(libft_dir)/libft.a

# ****************

libex_dir	= $(lib_dir)/libex
libex		= $(libex_dir)/libex.a

# ****************

libhash_dir	= $(lib_dir)/libhash
libhash		= $(libhash_dir)/libhash.a

# ***********************************

all			: $(NAME)

$(NAME)		: $(obj) $(lib)
	$(CC) $(CFLAGS) $(obj) -o $(NAME) $(LIBS)

clean		: lib_clean
	$(RM) $(obj)
	/bin/rm -rf $(NAME).dSYM

fclean		: lib_fclean
	$(RM) $(obj)
	$(RM) $(NAME)

re			: fclean all

# ***********************************

init		:
	zsh header.sh $(src_dir) includes/shell.h Makefile $(src_dir)
	zsh header.sh $(libft_dir) $(libft_dir)/libft.h $(libft_dir)/Makefile
	zsh header.sh $(libex_dir) $(libex_dir)/libex.h $(libex_dir)/Makefile
	zsh header.sh $(libhash_dir) $(libhash_dir)/libhash.h $(libhash_dir)/Makefile

get_module	:
	git submodule update --init

test		: get_module
	bash ./tests/all-test.sh tests

test_unit	: get_module
	bash ./tests/all-test.sh ./tests/unit-test $(TARGET)

test_issue	: get_module
	bash ./tests/all-test.sh ./tests/issue $(TARGET)

leak		: $(obj) $(lib)
	$(CC) $(CFLAGS) $(obj) $(LIBS) $(sharedlib) -o $(NAME)

sani-debug	: fclean lib_sani-debug
	$(MAKE) CFLAGS="$(CFLAGS) -fsanitize=address" $(lib)
	$(MAKE) clean

norm:
	@printf "\e[31m"; norminette $(src_dir) $(includes) ./libft \
	| grep -v -e ": OK!" -v -e "Missing or invalid header. Header are being reintroduced as a mandatory part of your files. This is not yet an error." \
	&& exit 1 \
	|| printf "\e[32m%s\n\e[m" "Norm OK!"; printf "\e[m"

tests/%/main.c: $(lib) FORCE
	$(CC) $(CFLAGS) $@ $(filter-out srcs/./main.c,$(src:%.c=$(src_dir)/%.c)) -o $(subst main.c,a.out,$@) $(LIBS)

tests/%/main.c+leak: $(lib) $(sharedlib)
	$(CC) $(CFLAGS) $(subst +leak,,$@) $(filter-out srcs/./main.c,$(src:%.c=$(src_dir)/%.c)) $(sharedlib) -o $(subst main.c+leak,a.out,$@) $(LIBS)

tests/%/main.c+sani: $(lib)
	$(CC) $(CFLAGS) -fsanitize=address $(subst +sani,,$@) $(filter-out srcs/./main.c,$(src:%.c=$(src_dir)/%.c)) -o $(subst main.c+sani,a.out,$@) $(LIBS)

prepush		: norm test

# ***********************************

$(libft): $(libft_dir)/*.c
	$(MAKE) -C $(libft_dir)

$(libex): $(libex_dir)/*.c
	$(MAKE) -C $(libex_dir)

$(libhash): $(libhash_dir)/*.c
	$(MAKE) -C $(libhash_dir)

lib_make	:$(libft) $(libex) $(libhash)

lib_clean	:
	$(MAKE) clean -C $(libft_dir)
	$(MAKE) clean -C $(libex_dir)
	$(MAKE) clean -C $(libhash_dir)

lib_fclean	:
	$(MAKE) fclean -C $(libft_dir)
	$(MAKE) fclean -C $(libex_dir)
	$(MAKE) fclean -C $(libhash_dir)

lib_sani-debug	:
	$(MAKE) -C $(libft_dir)
	$(MAKE) sani-debug -C $(libex_dir)
	$(MAKE) sani-debug -C $(libhash_dir)

FORCE:
