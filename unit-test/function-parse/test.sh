test_res_print() {
	if [ $1 -ne 0 ]; then
		printf "    \e[31m%s\n\e[m" "unit test KO!"
	else
		printf "    \e[32m%s\n\e[m" "unit test OK!"
	fi
}

DIR="$(dirname "$0")"

EXIT_CODE=0
for path in $(find $DIR -type f -name "*.c");
do
	echo $path
	gcc -g $INCLUDES \
	"$path" \
	$(find $REPO_ROOT/srcs/lex/ -type f -name "*.c") \
	$(find $REPO_ROOT/srcs/parse/ -type f -name "*.c" -not -name 'parse.c') \
	$SHARED_LIB $LIBS -lft -lex -lreadline

	./a.out
	AOUT=$?

	if [ $AOUT -ne 0 ]; then
		EXIT_CODE=1
		printf "\e[31m%s\n\e[m" ">>  KO!"
	else
		printf "\e[32m%s\n\e[m" ">>  OK!"
	fi
done
