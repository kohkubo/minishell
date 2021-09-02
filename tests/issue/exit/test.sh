#!/bin/bash

cp ./minishell "$(dirname "$0")"

cd "$(dirname "$0")" || exit

echo $PWD

for file in $(ls *.txt); do
	# echo "----------------"
	echo "Testing $file"
	# cat "$file"
	./minishell < $file >> output 2>&1
	exit_status_minishell=$?
	zsh < $file >> expect 2>&1
	exit_status_zsh=$?
	# echo "minishell $exit_status_minishell"
	# echo "zsh       $exit_status_zsh"
	if [ $exit_status_zsh -ne $exit_status_minishell ]; then
		echo "FAIL: $file"
		RES=1
	fi
	diff output expect
	if [ $? -ne 0 ]; then
		echo "FAIL: $file"
		RES=1
	fi
	rm -rf output expect
done

rm -f a.out leaksout minishell
rm -rf a.out.dSYM

exit $RES
