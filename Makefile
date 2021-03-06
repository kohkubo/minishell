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
obj_bonus	= $(src_bonus:%.c=$(src_dir)/%.o)
BONUS_FLG	= .bonus_flg

# ***********************************

CC 			= gcc
LIBS		= -L./libft/libft -L./libft/libex -L./libft/libhash \
				-lft -lex -lhash -lreadline -lhistory -L$(shell brew --prefix readline)/lib
CFLAGS		= -Wall -Wextra -Werror -O3 -g $(includes:%=-I%) -I$(shell brew --prefix readline)/include

# ***********************************

src =\
	./lex/lex.c \
	./lex/heredoc.c \
	./lex/data.c \
	./lex/store.c \
	./built-in/ft_exit.c \
	./built-in/echo.c \
	./built-in/ft_env.c \
	./built-in/ft_export.c \
	./built-in/ft_unset.c \
	./built-in/ft_cd.c \
	./built-in/ft_pwd.c \
	./main.c \
	./utils/get_fullpath.c \
	./env/env.c \
	./parse/parse.c \
	./parse/astree.c \
	./parse/command_line.c \
	./parse/job.c \
	./parse/command.c \
	./parse/redirection_list.c \
	./parse/redirection.c \
	./parse/token_list.c \
	./execute/exec.c \
	./execute/cmdline.c \
	./execute/job.c \
	./execute/cmd.c \
	./execute/redirection.c \
	./execute/simplecmd.c \
	./execute/builtin.c \
	./execute/error.c \
	./expand/expand.c \
	./expand/expand_astree.c \
	./signal/minishell_signal.c \

# ***********************************

src_bonus =\
	./lex/lex_bonus.c \
	./lex/heredoc.c \
	./lex/data.c \
	./lex/store_bonus.c \
	./built-in/ft_exit.c \
	./built-in/echo.c \
	./built-in/ft_env.c \
	./built-in/ft_export.c \
	./built-in/ft_unset.c \
	./built-in/ft_cd.c \
	./built-in/ft_pwd.c \
	./main.c \
	./utils/get_fullpath.c \
	./env/env.c \
	./parse/parse.c \
	./parse/astree.c \
	./parse/command_line.c \
	./parse/job.c \
	./parse/command.c \
	./parse/redirection_list.c \
	./parse/redirection.c \
	./parse/token_list.c \
	./execute/exec.c \
	./execute/cmdline.c \
	./execute/job.c \
	./execute/cmd.c \
	./execute/redirection.c \
	./execute/simplecmd.c \
	./execute/builtin.c \
	./execute/error.c \
	./expand/expand.c \
	./expand/expand_astree.c \
	./signal/minishell_signal.c \

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

all					: $(NAME)

$(NAME)				: $(obj) $(lib)
	$(CC) $(CFLAGS) $(obj) -o $(NAME) $(LIBS)
	@$(RM) $(BONUS_FLG)

bonus			: $(BONUS_FLG)

$(BONUS_FLG)	: $(obj_bonus) $(lib)
	$(CC) $(CFLAGS) $(obj_bonus) -o $(NAME) $(LIBS)
	@touch $(BONUS_FLG)

clean			: lib_clean
	$(RM) $(obj)
	$(RM) -r $(NAME).dSYM
	$(RM) leaksout

fclean			: clean lib_fclean
	$(RM) $(obj)
	$(RM) $(NAME)
	@$(RM) $(BONUS_FLG)

re			: fclean all

brew		:
	curl -fsSL https://rawgit.com/kube/42homebrew/master/install.sh | zsh

readline	:
	brew install readline

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

leak		: $(obj) $(lib)
	$(CC) $(CFLAGS) $(obj) $(LIBS) $(sharedlib) -o $(NAME)

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
