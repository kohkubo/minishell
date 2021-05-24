#!/bin/bash

# make -C libft/libex > /dev/null

test_res_print() {
	if [ $1 -ne 0 ]; then
		printf "    \e[31m%s\n\e[m" "unit test KO!"
	else
		printf "    \e[32m%s\n\e[m" "unit test OK!"
	fi
}

cd "$(dirname "$0")" || exit

for path in $(find . -type f -name "*.c");
do
	echo $path
	gcc -g -O3 -fsanitize=address "$path" $REPO_ROOT/libft/libft/libft.a $REPO_ROOT/libft/libex/libex.a
	./a.out
	if [ $? -ne 0 ]; then
		printf "\e[31m%s\n\e[m" ">>  KO!"
	else
		printf "\e[32m%s\n\e[m" ">>  OK!"
	fi
done

rm ./a.out
