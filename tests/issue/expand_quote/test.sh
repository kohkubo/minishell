#!/bin/bash

cp ./minishell "$(dirname "$0")"

cd "$(dirname "$0")" || exit

echo $PWD

for file in $(ls *.txt); do
	echo -n "--Testing $file "
	./minishell < $file > output #2>&1
	zsh < $file > expect #2>&1
	diff expect output > /dev/null
	if [ $? -ne 0 ]; then
		echo -e "\033[31m ×"
		cat $file
		echo "FAIL: $file"
		diff -y -W 80 expect output
		echo -e "\033[m"
		RES=1
	else
		echo -e "\033[32m ✓ \033[m"
	fi
	rm -rf output expect
done

rm -f a.out leaksout minishell
rm -rf a.out.dSYM

exit $RES
