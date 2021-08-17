#!/bin/bash

test_res_print() {
	if [ $1 -ne 0 ]; then
		printf "    \e[31m%s\n\e[m" "unit test KO!"
	else
		printf "    \e[32m%s\n\e[m" "unit test OK!"
	fi
}

DIR=$(dirname "$0")

make re -C libft/libdebug > /dev/null

EXIT_CODE=0
for path in $(find $DIR -type f -name "*.c");
do
	echo $path
	gcc -g -O3 "$path" $INCLUDES $LIBS\
	-lft -lex -lhash -ldebug \
	$SHARED_LIB

	./a.out
	RES=$?

	if [ $RES -ne 0 ]; then
		EXIT_CODE=1
		printf "\e[31m%s\n\e[m" ">>  KO!"
	else
		printf "\e[32m%s\n\e[m" ">>  OK!"
	fi
done

make sani-debug -C libft/libhash > /dev/null
make sani-debug -C libft/libdebug > /dev/null

for path in $(find $DIR -type f -name "*.c");
do
	gcc -g -O3 "$path" -fsanitize=address $INCLUDES $LIBS\
	-lft -lex -lhash -ldebug

	./a.out
	RES=$?
	if [ $RES -ne 0 ]; then
		EXIT_CODE=1
		printf "\e[31m%s\n\e[m" ">>  KO!"
	else
		printf "\e[32m%s\n\e[m" ">>  OK!"
	fi
done

rm -f ./a.out leaksout
rm -rf ./a.out.dSYM

make re -C libft/libhash > /dev/null
make re -C libft/libdebug > /dev/null

exit $EXIT_CODE
