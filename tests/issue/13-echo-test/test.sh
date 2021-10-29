#!/bin/bash

function test() {
	echo $1 | ./minishell | cat - <(echo "") | sed "1d" | sed "s/minishell> //g" >> output
	LEAKS=$(($LEAKS | $?))
	echo $1 | bash | cat - <(echo "") >> expect
}

cp ./minishell "$(dirname "$0")"
cd "$(dirname "$0")" || exit
rm -rf leaksout expect output

LEAKS=0
test "echo"
test "echo a"
test "echo aaaa"
test "echo test test pwd echo"
test "echo test*ttest"
test "echo あいう"
# test "echo aiueo\n" # 解釈しない
test "echo -"
test "echo -n"
test "echo -n test test tset"
# test "echo -n -n\n"
test "echo -n -n -n hello"
test "echo -n -n -n"
test "echo -n -n hello -n"
test "echo hello -n -n"

diff -y output expect
RES=$?

rm -rf leaksout expect output ./minishell
cd "$PWD" || exit

exit $(($RES | $LEAKS))
