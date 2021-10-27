#!/bin/bash

cp ./minishell "$(dirname "$0")"

cd "$(dirname "$0")" || exit

echo $PWD

rm -rf expect output

for file in $(ls *.txt); do
	# echo "Testing $file"
	# ./minishell < $file | sed '/minishell> /d' >> output 2>&1
	./minishell < $file >> output 2>&1
	sed -i "" -e "/minishell> /d" output
	sed -i "" -e "/heredoc... /d" output
	zsh < $file >> expect 2>&1
	diff expect output &> /dev/null
	if [ $? -ne 0 ]; then
		echo "FAIL: $file"
		cat $file
		diff expect output -y
		RES=1
		exit $RES
	fi
	rm -rf output expect
done

rm -f a.out leaksout minishell
rm -rf a.out.dSYM

exit $RES
