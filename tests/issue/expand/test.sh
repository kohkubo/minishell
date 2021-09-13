#!/bin/bash

cp ./minishell "$(dirname "$0")"

cd "$(dirname "$0")" || exit

echo $PWD

for file in $(ls *.txt); do
	echo "Testing $file"
	./minishell < $file >> output 2>&1
	zsh < $file >> expect 2>&1
	diff expect output
	if [ $? -ne 0 ]; then
		echo "FAIL: $file"
		RES=1
	fi
	rm -rf output expect
done

rm -f a.out leaksout minishell
rm -rf a.out.dSYM

exit $RES
