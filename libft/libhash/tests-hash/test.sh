#!/bin/bash

cd "$(dirname "${BASH_SOURCE}")"

make -C .. > /dev/null
make -C ../../libft > /dev/null
make -C ../../libex > /dev/null

EXIT_CODE=0
for path in $(find . -type f -name "*.c" -not -name 'sharedlib.c' -not -name 'catch_error.c');
do
	echo "$path"
	gcc -g \
		-I./../../libft \
		-L./../../libft \
		-lft \
		-I./../../libex \
		-L./../../libex \
		-lex \
		-I./../ \
		-L./../ \
		-lhash \
		$path \
		catch_error.c \
		sharedlib.c
	./a.out
	if [ $? -ne 0 ]; then
		EXIT_CODE=1
		echo $path
		printf "\e[31m%s\n\e[m" ">>  KO!"
	else
		printf "\e[32m%s\n\e[m" ">>  OK!"
	fi
done

make sani-debug -C .. > /dev/null

echo ""
echo "Sanitaize address check"

for path in $(find . -type f -name "*.c" -not -name 'sharedlib.c' -not -name 'catch_error.c');
do
	echo "$path"
	gcc -g -fsanitize=address \
		-I./../../libft \
		-L./../../libft \
		-I./../../libex \
		-L./../../libex \
		-lex \
		-lft \
		-I./../ \
		-L./../ \
		-lhash \
		$path \
		catch_error.c \
		sharedlib.c
	./a.out
	if [ $? -ne 0 ]; then
		EXIT_CODE=1
		echo $path
		printf "\e[31m%s\n\e[m" ">>  KO!"
	else
		printf "\e[32m%s\n\e[m" ">>  OK!"
	fi
done

rm -rf ./a.out leaksout
rm -rf ./a.out.dSYM

make fclean -C .. > /dev/null

exit $EXIT_CODE
