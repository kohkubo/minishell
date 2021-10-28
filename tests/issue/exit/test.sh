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
	sed -i "" -e "/minishell> /d" output
	echo "exit" >> expect
	bash < $file >> expect 2>&1
	exit_status_bash=$?
	if [ $exit_status_bash -ne $exit_status_minishell ]; then
		echo "FAIL: $file"
		echo "minishell $exit_status_minishell"
		echo "bash      $exit_status_bash"
		RES=1
	fi
	diff output <(sed "s/bash: line 1: /minishell: /g" expect)
	if [ $? -ne 0 ]; then
		echo "FAIL: $file"
		RES=1
	fi
	rm -rf output expect
done

rm -f a.out leaksout minishell
rm -rf a.out.dSYM

exit $RES
