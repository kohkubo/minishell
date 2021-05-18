#!/bin/bash

set -e

cp ./minishell "$(dirname "$0")"
cd "$(dirname "$0")" || exit

echo "echo test test pwd echo" | ./minishell > output
echo "echo test test pwd echo" | bash > expect

echo "echo" | ./minishell >> output
echo "echo" | bash >> expect

echo "echo aaaa" | ./minishell >> output
echo "echo aaaa" | bash >> expect

echo "echo -n" | ./minishell >> output
echo "echo -n" | bash >> expect

echo "echo -n test test tset" | ./minishell >> output
echo "echo -n test test tset" | bash >> expect

echo "echo a" | ./minishell >> output
echo "echo a" | bash >> expect

echo "echo test*ttest" | ./minishell >> output
echo "echo test*ttest" | bash >> expect

echo "echo あいう" | ./minishell >> output
echo "echo あいう" | bash >> expect

diff output expect
RES=$?
rm expect output ./minishell
cd "$PWD" || exit
exit $RES
