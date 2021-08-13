#!/bin/bash

make leak > /dev/null

set -e

cp minishell "$(dirname "$0")"
cd "$(dirname "$0")" || exit

echo "exit" | ./minishell
echo $? > output
echo "exit" | bash
echo $? > expect

echo "exit 0" | ./minishell
echo $? >> output
echo "exit 0" | bash
echo $? >> expect

echo "exit 1" | ./minishell
echo $? >> output
echo "exit 1" | bash
echo $? >> expect

echo "exit 255" | ./minishell
echo $? >> output
echo "exit 255" | bash
echo $? >> expect

echo "exit 256" | ./minishell
echo $? >> output
echo "exit 256" | bash
echo $? >> expect

echo "exit -1" | ./minishell
echo $? >> output
echo "exit -1" | bash
echo $? >> expect

echo "exit -344" | ./minishell
echo $? >> output
echo "exit -344" | bash
echo $? >> expect

echo "exit 300" | ./minishell
echo $? >> output
echo "exit 300" | bash
echo $? >> expect

echo "exit 21474836477" | ./minishell
echo $? >> output
echo "exit 21474836477" | bash
echo $? >> expect

echo "exit aaaa" | ./minishell 2>> output
echo $? >> output
echo "minishell: line 1: exit: aaaa: numeric argument required" >> expect
echo "exit aaaa" | bash
echo $? >> expect

diff output expect

RES=$?
rm expect output ./minishell
cd "$PWD" || exit
rm -f srcs/main.o
exit $RES
