#!/bin/bash

make bonus
cp ./minishell "$(dirname "$0")"

cd "$(dirname "$0")" || exit

echo $PWD

rm -rf output expect
chmod -r resources/no_read_perm
chmod -w resources/no_write_perm

for file in $(ls *.txt); do
	echo -n "$file ... "
	./minishell < $file > output 2>&1
	sed -i "" -e "/minishell> /d" -e "/heredoc... /d" output
	bash < $file 2>&1 | sed -e 's/bash: line .: /minishell: /g' > expect
	diff expect output > /dev/null
	if [ $? -ne 0 ]; then
		printf "\e[31m%s\n\n\e[m" "×"
		echo $file
		cat -n $file
		printf "\e[31m\e[1m%37s | %s\e[m\n" "expect" "actuary"
		printf "\e[31m"
		python -c "print '-'*38 + '+' + '-'*38"
		diff -y -W 79 expect output
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

cd "$REPO_ROOT" || exit

make re

exit $RES
