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

# ***********************************

NAME		= minishell
includes	= includes
src_dir		= srcs
obj_dir		= objs
obj			= $(src:%.c=$(src_dir)/%.o)

# ***********************************

CC 			= gcc
CFLAGS		= -Wall -Wextra -Werror -O3 -I$(includes)

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

# ****************

libdebug_dir	= $(lib_dir)/libdebug
libdebug		= $(libdebug_dir)/libdebug.a

# ***********************************

all			: $(NAME)

$(NAME)		: $(obj) $(lib)
	$(CC) $(CFLAGS) $(obj) $(lib) -o $(NAME) -lreadline

clean		: lib_clean
	$(RM) $(obj)

fclean		: lib_fclean
	$(RM) $(obj)
	$(RM) $(NAME)

re			: fclean all

# ***********************************

init		:
	zsh header.sh $(src_dir) $(includes)/shell.h Makefile $(src_dir)
	zsh header.sh $(libft_dir) $(libft_dir)/libft.h $(libft_dir)/Makefile
	zsh header.sh $(libex_dir) $(libex_dir)/libex.h $(libex_dir)/Makefile
	zsh header.sh $(libhash_dir) $(libhash_dir)/libhash.h $(libhash_dir)/Makefile
	zsh header.sh $(libdebug_dir) $(libdebug_dir)/libdebug.h $(libdebug_dir)/Makefile

get_module	:
	git submodule update --init

test		: get_module
	bash ./tests/all-test.sh tests

test_unit	: get_module
	bash ./tests/all-test.sh ./tests/unit-test $(TARGET)

test_issue	: get_module
	bash ./tests/all-test.sh ./tests/issue $(TARGET)

leak		: $(obj) $(lib) $(libdebug)
	$(CC) $(CFLAGS) $(obj) $(lib) $(libdebug) $(sharedlib) -o $(NAME) -lreadline

debug		: fclean lib_debug
	$(MAKE) CFLAGS="$(CFLAGS) -D DEBUG=1 -g" lib="$(lib) $(libdebug)"
	$(MAKE) clean

sani-debug	: fclean lib_sani-debug
	$(MAKE) CFLAGS="$(CFLAGS) -D DEBUG=1 -g -fsanitize=address" lib="$(lib) $(libdebug)"
	$(MAKE) clean

norm		:
	norminette $(src_dir) $(includes) ./libft \
	|| (printf "\e[31m%s\n\e[m" "Norm KO!"; exit 1)
	@printf "\e[32m%s\n\e[m" "Norm OK!"

%/main.c: $(lib) FORCE
	$(CC) $(CFLAGS) $@ $(filter-out srcs/./main.c,$(src:%.c=$(src_dir)/%.c)) $(lib) -o $(subst main.c,a.out,$@) -lreadline

%/main.c+leak: $(lib) $(sharedlib)
	$(CC) $(CFLAGS) $(subst +leak,,$@) $(filter-out srcs/./main.c,$(src:%.c=$(src_dir)/%.c)) $^ -o $(subst main.c+leak,a.out,$@) -lreadline

%/main.c+sani: $(lib) (libdebug) $(sharedlib)
	$(CC) $(CFLAGS) -D DEBUG=1 -g -fsanitize=address $(subst +leak,,$@) $(filter-out srcs/./main.c,$(src:%.c=$(src_dir)/%.c)) $^ -o $(subst main.c+leak,a.out,$@) -lreadline

prepush		: norm test

# ***********************************

$(libft): $(libft_dir)/*.c
	$(MAKE) -C $(libft_dir)

$(libex): $(libex_dir)/*.c
	$(MAKE) -C $(libex_dir)

$(libhash): $(libhash_dir)/*.c
	$(MAKE) -C $(libhash_dir)

$(libdebug): $(libdebug_dir)/*.c
	$(MAKE) -C $(libdebug_dir)

lib_make	:$(libft) $(libex) $(libhash)

lib_clean	:
	$(MAKE) clean -C $(libft_dir)
	$(MAKE) clean -C $(libex_dir)
	$(MAKE) clean -C $(libhash_dir)
	$(MAKE) clean -C $(libdebug_dir)

lib_fclean	:
	$(MAKE) fclean -C $(libft_dir)
	$(MAKE) fclean -C $(libex_dir)
	$(MAKE) fclean -C $(libhash_dir)
	$(MAKE) fclean -C $(libdebug_dir)

lib_debug	:
	$(MAKE) re -C $(libft_dir)
	$(MAKE) debug -C $(libex_dir)
	$(MAKE) debug -C $(libhash_dir)
	$(MAKE) debug -C $(libdebug_dir)

lib_sani-debug	: fclean
	$(MAKE) re -C $(libft_dir)
	$(MAKE) sani-debug -C $(libex_dir)
	$(MAKE) sani-debug -C $(libhash_dir)
	$(MAKE) sani-debug -C $(libdebug_dir)

FORCE:
