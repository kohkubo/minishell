DIR="$(dirname "$0")"

EXIT_CODE=0
gcc -g $INCLUDES \
-o "$DIR/a.out" \
"$DIR/test.c" \
"$REPO_ROOT/srcs/utils/get_fullpath.c" \
$(find $REPO_ROOT/srcs/lex -type f -name "*.c" -not -name '*_bonus.c') \
$(find $REPO_ROOT/srcs/parse/ -type f -name "*.c") \
$(find $REPO_ROOT/srcs/execute/ -type f -name "*.c") \
$(find $REPO_ROOT/srcs/built-in/ -type f -name "*.c") \
$(find $REPO_ROOT/srcs/expand/ -type f -name "*.c") \
$(find $REPO_ROOT/srcs/signal/ -type f -name "*.c") \
$REPO_ROOT/srcs/env/env.c \
$LIBS -lft -lex -lhash -lreadline -lhistory -L$(brew --prefix readline)/lib -I$(brew --prefix readline)/include $SHARED_LIB

tests=(
	# exec_with_path 経路のテスト
	"ls"
	"ls ."
	"cat Makefile"

	# 直exec 経路のテスト
	"$DIR/tester.py"
	"$DIR/tester.py arg1 arg2"

	# built-in 経路のテスト(command not foundじゃないことの確認)
	"unset"
	"exit"

	# PIPEのテスト
	"cat Makefile | grep a"
	"echo aaaaaaaa | cat | cat | cat | cat | wc"
	"export TEST=AAA | echo \$TEST"
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
		echo "AOUT_EXIT_CODE: $AOUT"
		diff -y "$DIR/out" "$DIR/expect"
		printf "\e[31m%s\n\e[m" ">>  KO!"
		exit
	fi
done

echo "--- error case ---"

errors=(
	"no_exist_command"
	"./no_exist_exe"
	"$DIR/no_perm.py"

	# PIPEのテスト
	"cat no_exists_file | cat | cat | cat | wc"
	"$DIR/no_perm.py | cat | cat | cat | wc"
	"cat no_exists_file | cat | cat | cat | no_exist_command"
	"cat no_exists_file | cat | cat | cat | ./no_exist_exe"
	"cat no_exists_file | cat | cat | cat | $DIR/no_perm.py"
)

for i in ${!errors[@]};
do
	echo "./a.out ${errors[$i]}"
	echo "${errors[$i]}" | bash &> /dev/stdout | sort > $DIR/expect
	BASH_EXIT_CODE=$?
	"$DIR/a.out" "${errors[$i]}" &> /dev/stdout \
		| sed 's/minishell:/bash: line 1:/' \
		| sort > $DIR/out
	AOUT_EXIT_CODE=$?

	diff "$DIR/out" "$DIR/expect" > /dev/null
	if [ $? -eq 0 ] && [ $AOUT_EXIT_CODE -eq $BASH_EXIT_CODE ]; then
	# if [ $? -eq 0 ] && [ $AOUT_EXIT_CODE -ne 0 ]; then
		printf "\e[32m%s\n\e[m" ">>  OK!"
	else
		EXIT_CODE=1
		echo "AOUT_EXIT_CODE: $AOUT_EXIT_CODE, BASH_EXIT_CODE: $BASH_EXIT_CODE"
		diff "$DIR/out" "$DIR/expect" -y
		printf "\e[31m%s\n\e[m" ">>  KO!"
	fi
done

rm -f $DIR/a.out leaksout $DIR/out $DIR/expect

exit $EXIT_CODE
