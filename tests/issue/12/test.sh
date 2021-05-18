#!/bin/bash

set -e

cp ./minishell "$(dirname "$0")"
cd "$(dirname "$0")" || exit

# 通常出力
echo "test" | ./minishell > output
echo "test" > expect

# スペース区切り
echo "aaa bbb ccc" | ./minishell >> output
echo -e 'aaa\nbbb\nccc' >> expect

echo "echo" | ./minishell >> output
echo "echo is not implemented yet" >> expect

echo "cd" | ./minishell >> output
echo "cd is not implemented yet" >> expect

echo "pwd" | ./minishell >> output
echo "pwd is not implemented yet" >> expect

echo "export" | ./minishell >> output
echo "export is not implemented yet" >> expect

echo "unset" | ./minishell >> output
echo "unset is not implemented yet" >> expect

echo "env" | ./minishell >> output
echo "env is not implemented yet" >> expect

echo "exit" | ./minishell >> output
echo "exit is not implemented yet" >> expect

echo "cd cd cd" | ./minishell >> output
echo "cd is not implemented yet" >> expect

echo " pwd echo" | ./minishell >> output
echo "pwd is not implemented yet" >> expect

echo "aaa echo" | ./minishell >> output
echo -e "aaa\necho" >> expect

echo "" | ./minishell
echo "    " | ./minishell

diff output expect
RES=$?
rm expect output ./minishell
cd "$PWD" || exit
exit $RES
