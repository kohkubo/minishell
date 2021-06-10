test_res_print() {
	if [ $1 -ne 0 ]; then
		printf "    \e[31m%s\n\e[m" "unit test KO!"
	else
		printf "    \e[32m%s\n\e[m" "unit test OK!"
	fi
}

cd "$(dirname "$0")" || exit

EXIT_CODE=0
for path in $(find . -type f -name "*.c");
do
	echo $path
	gcc -o "minishell" -g -I$REPO_ROOT/includes -I$REPO_ROOT/libft/libft \
	"$path" \
	$(find $REPO_ROOT/srcs/lex/ -type f -name "*.c") \
	$(find $REPO_ROOT/srcs/parse/ -type f -name "*.c" -not -name 'parse.c') \
	$REPO_ROOT/libft/libft/libft.a \
	$REPO_ROOT/libft/libex/libex.a \
	$REPO_ROOT/libft/libhash/libhash.a \
	$REPO_ROOT/libft/libdebug/libdebug.a \
	$SHARED_LIB

	./minishell
	AOUT=$?

	if [ $AOUT -ne 0 ]; then
		EXIT_CODE=1
		printf "\e[31m%s\n\e[m" ">>  KO!"
	else
		printf "\e[32m%s\n\e[m" ">>  OK!"
	fi
done
