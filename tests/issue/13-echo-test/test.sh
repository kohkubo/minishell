#!/bin/bash

function test() {
	echo $1 | ./minishell | sed '1d' | sed "s/minishell> //g" >> output
	LEAKS=$(($LEAKS | $?))
	echo $1 | bash >> expect
}

function newline() {
	echo "" >> output
	echo "" >> expect
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
test "echo -"
test "echo -n"
newline
test "echo -n test test tset"
newline
test "echo -n -n -n hello"
newline
test "echo -n -n -n"
newline

diff output expect
RES=$?

rm leaksout expect output ./minishell
cd "$PWD" || exit

exit $(($RES | $LEAKS))
