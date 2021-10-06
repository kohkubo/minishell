#!/bin/bash

cp ./minishell "$(dirname "$0")"

cd "$(dirname "$0")" || exit

echo $PWD

rm -rf output expect

for file in $(ls *.txt); do
	echo -n "$file ... "
	./minishell < $file > output 2>&1
	bash < $file 2>&1 | sed 's/bash: line 1: //g' > expect
	diff expect output > /dev/null
	if [ $? -ne 0 ]; then
		printf "\e[31m%s\n\n\e[m" "×"
		cat -n $file
		printf "\e[31m"
		diff -y -W 80 expect output
		printf "\e[m\n"
		RES=1
		exit $RES
	else
		printf "\e[32m%s\n\e[m" "✓"
	fi
	rm -rf output expect
done

rm -f a.out leaksout minishell
rm -rf a.out.dSYM

exit $RES
