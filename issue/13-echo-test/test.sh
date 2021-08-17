#!/bin/bash

make srcs/main.c+leak > /dev/null

mv srcs/a.out "$(dirname "$0")"
cd "$(dirname "$0")" || exit

LEAKS=0

echo "echo test test pwd echo" | ./a.out > output
LEAKS=$(($LEAKS | $?))
echo "echo test test pwd echo" | bash > expect

echo "echo" | ./a.out >> output
LEAKS=$(($LEAKS | $?))
echo "echo" | bash >> expect

echo "echo aaaa" | ./a.out >> output
LEAKS=$(($LEAKS | $?))
echo "echo aaaa" | bash >> expect

echo "echo -n" | ./a.out >> output
LEAKS=$(($LEAKS | $?))
echo "echo -n" | bash >> expect

echo "echo -n test test tset" | ./a.out >> output
LEAKS=$(($LEAKS | $?))
echo "echo -n test test tset" | bash >> expect

echo "echo a" | ./a.out >> output
LEAKS=$(($LEAKS | $?))
echo "echo a" | bash >> expect

echo "echo test*ttest" | ./a.out >> output
LEAKS=$(($LEAKS | $?))
echo "echo test*ttest" | bash >> expect

echo "echo あいう" | ./a.out >> output
LEAKS=$(($LEAKS | $?))
echo "echo あいう" | bash >> expect

diff output expect
RES=$?
rm leaksout expect output ./a.out
cd "$PWD" || exit

exit $(($RES | $LEAKS))
