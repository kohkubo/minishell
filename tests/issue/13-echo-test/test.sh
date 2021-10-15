#!/bin/bash

cp ./minishell "$(dirname "$0")"
cd "$(dirname "$0")" || exit

LEAKS=0

echo "echo test test pwd echo" | ./minishell > output
LEAKS=$(($LEAKS | $?))
echo "echo test test pwd echo" | bash > expect

echo "echo" | ./minishell >> output
LEAKS=$(($LEAKS | $?))
echo "echo" | bash >> expect

echo "echo aaaa" | ./minishell >> output
LEAKS=$(($LEAKS | $?))
echo "echo aaaa" | bash >> expect

echo "echo -n" | ./minishell >> output
LEAKS=$(($LEAKS | $?))
echo "echo -n" | bash >> expect

echo "echo -" | ./minishell >> output
LEAKS=$(($LEAKS | $?))
echo "echo -" | bash >> expect

echo "echo" | ./minishell >> output
LEAKS=$(($LEAKS | $?))
echo "echo" | bash >> expect

echo "echo -n test test tset" | ./minishell >> output
LEAKS=$(($LEAKS | $?))
echo "echo -n test test tset" | bash >> expect

echo "echo a" | ./minishell >> output
LEAKS=$(($LEAKS | $?))
echo "echo a" | bash >> expect

echo "echo test*ttest" | ./minishell >> output
LEAKS=$(($LEAKS | $?))
echo "echo test*ttest" | bash >> expect

echo "echo あいう" | ./minishell >> output
LEAKS=$(($LEAKS | $?))
echo "echo あいう" | bash >> expect

diff output expect
RES=$?
rm leaksout expect output ./minishell
cd "$PWD" || exit

exit $(($RES | $LEAKS))
