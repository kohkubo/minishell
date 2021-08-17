#!/bin/bash

make srcs/main.c+leak > /dev/null

set -e

cp srcs/a.out "$(dirname "$0")"
cd "$(dirname "$0")" || exit

echo "exit" | ./a.out
echo $? > output
echo "exit" | bash
echo $? > expect

echo "exit 0" | ./a.out
echo $? >> output
echo "exit 0" | bash
echo $? >> expect

echo "exit 1" | ./a.out
echo $? >> output
echo "exit 1" | bash
echo $? >> expect

echo "exit 255" | ./a.out
echo $? >> output
echo "exit 255" | bash
echo $? >> expect

echo "exit 256" | ./a.out
echo $? >> output
echo "exit 256" | bash
echo $? >> expect

echo "exit -1" | ./a.out
echo $? >> output
echo "exit -1" | bash
echo $? >> expect

echo "exit -344" | ./a.out
echo $? >> output
echo "exit -344" | bash
echo $? >> expect

echo "exit 300" | ./a.out
echo $? >> output
echo "exit 300" | bash
echo $? >> expect

echo "exit 21474836477" | ./a.out
echo $? >> output
echo "exit 21474836477" | bash
echo $? >> expect

echo "exit aaaa" | ./a.out 2>> output
echo $? >> output
echo "a.out: line 1: exit: aaaa: numeric argument required" >> expect
echo "exit aaaa" | bash
echo $? >> expect

diff output expect

RES=$?
rm expect output ./a.out
cd "$PWD" || exit
exit $RES
