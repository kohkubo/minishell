#!/bin/bash

set -e

echo "=============test13================"

cp minishell "$(dirname "$0")"
cd "$(dirname "$0")" || exit

echo "echo test test pwd echo" | minishell > output
echo "echo test test pwd echo" | bash > expect

echo "echo" | minishell >> output
echo "echo" | bash >> expect

echo "echo aaaa" | minishell >> output
echo "echo aaaa" | bash >> expect

echo "echo -n" | minishell >> output
echo "echo -n" | bash >> expect

echo "echo -n test test tset" | minishell >> output
echo "echo -n test test tset" | bash >> expect

echo "echo a" | minishell >> output
echo "echo a" | bash >> expect

echo "echo \n \n" | minishell >> output
echo "echo \n \n" | bash >> expect

echo "echo test\\ntest" | minishell >> output
echo "echo test\\ntest" | bash >> expect

echo "echo test\\cttest" | minishell >> output
echo "echo test\\cttest" | bash >> expect

echo "echo test\\vttest" | minishell >> output
echo "echo test\\vttest" | bash >> expect

echo "echo test\\vttest" | minishell >> output
echo "echo test\\vttest" | bash >> expect

echo "echo test*ttest" | minishell >> output
echo "echo test*ttest" | bash >> expect

diff output expect
export RES=$?
rm expect output minishell
cd "$PWD" || exit
exit $RES
