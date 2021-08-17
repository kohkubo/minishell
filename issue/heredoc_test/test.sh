#!/bin/bash

make tests/issue/heredoc_test/main.c+leak > /dev/null

cd "$(dirname "$0")" || exit

echo $PWD

for file in $(ls *.txt); do
	echo "Testing $file" >> output
	echo "--------------------------------" >> output
	cat $file >> output
	echo "--------------------------------" >> output
	./a.out < $file >> output 2>&1
	echo $? >> output
	echo "--------------------------------" >> output
	echo "" >> output
done

diff expect output
RES=$?

rm -f a.out output leaksout
rm -rf a.out.dSYM

exit $RES
