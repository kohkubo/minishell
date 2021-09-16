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
			FORCE \

# ***********************************

NAME		= minishell
includes	= ./includes ./libft/libft ./libft/libex ./libft/libhash
src_dir		= srcs
obj_dir		= objs
obj			= $(src:%.c=$(src_dir)/%.o)

# ***********************************

CC 			= gcc
LIBS		= -L./libft/libft -L./libft/libex -L./libft/libhash -lreadline -lhash -lex -lft
CFLAGS		= -Wall -Wextra -Werror -O3 -g $(includes:%=-I%)

# ***********************************

src =\
	./lex/lex.c \
	./lex/token.c \
	./lex/heredoc.c \
	./lex/data.c \
	./built-in/ft_exit.c \
	./built-in/echo.c \
	./built-in/ft_env.c \
	./built-in/ft_export.c \
	./built-in/ft_unset.c \
	./built-in/ft_pwd.c \
	./main.c \
	./error.c \
	./env/env.c \
	./parse/parse-v2.c \
	./parse/astree.c \
	./parse/command_line.c \
	./parse/job.c \
	./parse/command.c \
	./parse/redirection_list.c \
	./parse/redirection.c \
	./parse/simple_command.c \
	./parse/token_list.c \
	./execute/exec__main.c \
	./execute/exec_cmdline.c \
	./execute/exec_job.c \
	./execute/exec_cmd.c \
	./execute/exec_simplecmd.c \
	./expand/expand.c \

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

test		:
	bash ./tests/all-test.sh tests

test_unit	:
	bash ./tests/all-test.sh ./tests/unit-test $(TARGET)

test_issue	:
	bash ./tests/all-test.sh ./tests/issue $(TARGET)

Darwin_leak: $(obj) $(lib) $(DSTRCTR)
	$(CC) $(CFLAGS) $(obj) $(sharedlib) -o $(NAME) $(LIBS)

Linux_leak: $(lib)
	$(CC) $(CFLAGS) -fsanitize=address $(src:%.c=$(src_dir)/%.c) -o $(NAME) $(LIBS)

leak: $(shell uname)_leak

sani-debug	: fclean lib_sani-debug
	$(MAKE) CFLAGS="$(CFLAGS) -fsanitize=address" $(lib)
	$(MAKE) clean

norm:
	@printf "$(_RED)"; norminette $(src_dir) $(includes) ./libft \
	| grep -v -e ": OK!" -v -e "Missing or invalid header. Header are being reintroduced as a mandatory part of your files. This is not yet an error." \
	&& printf "$(_END)" && exit 1 \
	|| printf "$(_GREEN)%s\n$(_END)" "Norm OK!"

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

# Colors
# ****************************************************************************

_GREY	= \033[30m
_RED	= \033[31m
_GREEN	= \033[32m
_YELLOW	= \033[33m
_BLUE	= \033[34m
_PURPLE	= \033[35m
_CYAN	= \033[36m
_WHITE	= \033[37m
_END	= \033[0m
