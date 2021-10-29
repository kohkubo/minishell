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
$(find $REPO_ROOT/srcs/lex -type f -name "*.c" -not -name '*_bonus.c') \
$(find $REPO_ROOT/srcs/signal -type f -name "*.c") \
$(find $REPO_ROOT/srcs/parse -type f -name "*.c") \
$SHARED_LIB $LIBS -lft -lex -lreadline -lhistory -L$(brew --prefix readline)/lib -I$(brew --prefix readline)/include || exit 1

$DIR/a.out
AOUT=$?

if [ $AOUT -ne 0 ]; then
	EXIT_CODE=1
	printf "\e[31m%s\n\e[m" ">>  KO!"
	exit
else
	printf "\e[32m%s\n\e[m" ">>  OK!"
fi

echo "--- error_test ---"
gcc -g $INCLUDES \
-o $DIR/a.out \
"$DIR/for_error_test.c" \
$(find $REPO_ROOT/srcs/lex/ -type f -name "*.c") \
$(find $REPO_ROOT/srcs/signal -type f -name "*.c") \
$(find $REPO_ROOT/srcs/parse/ -type f -name "*.c") \
$SHARED_LIB $LIBS -lft -lex -lreadline -lhistory -L$(brew --prefix readline)/lib -I$(brew --prefix readline)/include || exit 1

$DIR/a.out 2> $DIR/out
AOUT=$?

diff $DIR/out $DIR/error_case_expect > /dev/null

if [ $? -ne 0 ] || [ $AOUT -ne 0 ]; then
	EXIT_CODE=1
	diff -y -W 80 $DIR/out $DIR/error_case_expect
	printf "\e[31m%s\n\e[m" ">>  KO!"
else
	printf "\e[32m%s\n\e[m" ">>  OK!"
fi

rm -f $DIR/a.out leaksout $DIR/out
rm -rf $DIR/a.out.dSYM

exit $EXIT_CODE
