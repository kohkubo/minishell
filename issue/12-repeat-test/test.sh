#!/bin/bash

make leak > /dev/null

cp ./minishell "$(dirname "$0")"
cd "$(dirname "$0")" || exit

LEAKS=0

# 通常出力
echo "test" | ./minishell > output
LEAKS=$(($LEAKS | $?))
echo "test" > expect

# スペース区切り
echo "aaa bbb ccc" | ./minishell >> output
LEAKS=$(($LEAKS | $?))
echo -e 'aaa\nbbb\nccc' >> expect

# echo "echo" | ./minishell >> output
# echo "echo is not implemented yet" >> expect

echo "cd" | ./minishell >> output
LEAKS=$(($LEAKS | $?))
echo "cd is not implemented yet" >> expect

echo "pwd" | ./minishell >> output
LEAKS=$(($LEAKS | $?))
echo "pwd is not implemented yet" >> expect

echo "export" | ./minishell >> output
LEAKS=$(($LEAKS | $?))
echo "export is not implemented yet" >> expect

echo "unset" | ./minishell >> output
LEAKS=$(($LEAKS | $?))
echo "unset is not implemented yet" >> expect

echo "env" | ./minishell >> output
LEAKS=$(($LEAKS | $?))
echo "env is not implemented yet" >> expect

echo "exit" | ./minishell >> output
LEAKS=$(($LEAKS | $?))
echo "exit is not implemented yet" >> expect

echo "cd cd cd" | ./minishell >> output
LEAKS=$(($LEAKS | $?))
echo "cd is not implemented yet" >> expect

echo " pwd echo" | ./minishell >> output
LEAKS=$(($LEAKS | $?))
echo "pwd is not implemented yet" >> expect

echo "aaa echo" | ./minishell >> output
LEAKS=$(($LEAKS | $?))
echo -e "aaa\necho" >> expect

echo "" | ./minishell
LEAKS=$(($LEAKS | $?))
echo "    " | ./minishell
LEAKS=$(($LEAKS | $?))

diff output expect
RES=$?
rm leaksout expect output ./minishell
cd "$PWD" || exit
rm -f srcs/main.o
exit $(($RES | $LEAKS))
