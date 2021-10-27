#!/bin/bash

cp ./minishell "$(dirname "$0")"

cd "$(dirname "$0")" || exit

echo $PWD

rm -rf output expect

for file in $(ls *.txt); do
	echo "--Testing $file"
	./minishell < $file > output 2>&1
	sed -i "" -e "/minishell> /d" output
	sed -i "" -e "/heredoc... /d" output
	zsh < $file > expect 2>&1
	diff expect output &> /dev/null
	if [ $? -ne 0 ]; then
		echo "FAIL: $file"
		cat -n $file
		printf "\e[31m"
		printf "%37s | %s\n" "expect" "output"
		perl -e 'print "-" x 79, "\n"'
		diff -y -W 79 expect output
		printf "\e[m"
		RES=1
		exit $RES
	fi
	rm -rf output expect
done

rm -f a.out leaksout minishell
rm -rf a.out.dSYM

exit $RES
