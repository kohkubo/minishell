DIR="$(dirname "$0")"

EXIT_CODE=0
gcc -g $INCLUDES \
-o "$DIR/a.out" \
"$DIR/test.c" \
$(find $REPO_ROOT/srcs/lex/ -type f -name "*.c") \
$(find $REPO_ROOT/srcs/parse/ -type f -name "*.c" -not -name 'parse.c') \
$(find $REPO_ROOT/srcs/execute/ -type f -name "*.c") \
$REPO_ROOT/srcs/env/env.c \
$LIBS -lft -lex -lhash -lreadline $SHARED_LIB

tests=(
	"ls"
	"ls ."
	"cat Makefile"
	"$DIR/tester.py"
	"$DIR/tester.py arg1 arg2"
	# "ls | cat | cat"
)

for i in ${!tests[@]};
do
	echo "./a.out ${tests[$i]}"
	echo "${tests[$i]}" | bash > $DIR/expect
	"$DIR/a.out" "${tests[$i]}" > $DIR/out
	AOUT=$?

	diff "$DIR/out" "$DIR/expect" > /dev/null
	if [ $? -eq 0 ] && [ $AOUT -eq 0 ]; then
		printf "\e[32m%s\n\e[m" ">>  OK!"
	else
		EXIT_CODE=1
		diff -y "$DIR/out" "$DIR/expect"
		printf "\e[31m%s\n\e[m" ">>  KO!"
	fi
done

rm -f $DIR/a.out leaksout $DIR/out $DIR/expect

exit $EXIT_CODE