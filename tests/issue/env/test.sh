#!/bin/bash

cp ./minishell "$(dirname "$0")"

cd "$(dirname "$0")" || exit

echo $PWD

for file in $(ls *.txt); do
	echo "File: $file"
	./minishell < $file >> output 2>&1
	bash < $file >> expect 2>&1
	grep -v -e "SHLVL" -v -e "_=" expect | sort --output=expect
	grep -v -e "SHLVL" -v -e "_=" output | sort --output=output
	diff expect output > /dev/null 2>&1
	if [ $? -ne 0 ]; then
		diff expect output -y
		echo "FAIL: $file"
		RES=1
	fi
	rm -rf output expect
done

rm -f a.out leaksout minishell
rm -rf a.out.dSYM

exit $RES
