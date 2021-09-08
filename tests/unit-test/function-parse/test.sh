test_res_print() {
	if [ $1 -ne 0 ]; then
		printf "    \e[31m%s\n\e[m" "unit test KO!"
	else
		printf "    \e[32m%s\n\e[m" "unit test OK!"
	fi
}

DIR="$(dirname "$0")"

EXIT_CODE=0
gcc -g $INCLUDES \
-o $DIR/a.out \
$DIR/test.c \
$(find $REPO_ROOT/srcs/lex/ -type f -name "*.c") \
$(find $REPO_ROOT/srcs/parse/ -type f -name "*.c" -not -name 'parse.c') \
$SHARED_LIB $LIBS -lft -lex -lreadline || exit 1

$DIR/a.out
AOUT=$?

if [ $AOUT -ne 0 ]; then
	EXIT_CODE=1
	printf "\e[31m%s\n\e[m" ">>  KO!"
else
	printf "\e[32m%s\n\e[m" ">>  OK!"
fi

rm -f $DIR/a.out leaksout


echo "--- error_test ---"
gcc -g $INCLUDES \
-o $DIR/a.out \
"$DIR/for_error_test.c" \
$(find $REPO_ROOT/srcs/lex/ -type f -name "*.c") \
$(find $REPO_ROOT/srcs/parse/ -type f -name "*.c" -not -name 'parse.c') \
$SHARED_LIB $LIBS -lft -lex -lreadline || exit 1

$DIR/a.out
AOUT=$?

if [ $AOUT -ne 0 ]; then
	EXIT_CODE=1
	printf "\e[31m%s\n\e[m" ">>  KO!"
else
	printf "\e[32m%s\n\e[m" ">>  OK!"
fi

rm -f a.out leaksout

exit $EXIT_CODE
