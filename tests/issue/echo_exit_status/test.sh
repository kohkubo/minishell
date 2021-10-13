#!/bin/bash

cp ./minishell "$(dirname "$0")"

cd "$(dirname "$0")" || exit

echo $PWD

rm -rf expect output

for file in $(ls *.txt); do
	echo "Testing $file"
	./minishell < $file >> output >&1
	bash < $file >> expect >&1
	
	cat $file
	diff -y expect output
	if [ $? -ne 0 ]; then
		echo "FAIL: $file"
		# cat $file
		# diff expect output -y
		RES=1
	fi
	rm -rf output expect
done

rm -f a.out leaksout minishell
rm -rf a.out.dSYM

exit $RES
