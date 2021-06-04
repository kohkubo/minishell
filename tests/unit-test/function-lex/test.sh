#!/bin/bash

test_res_print() {
	if [ $1 -ne 0 ]; then
		printf "    \e[31m%s\n\e[m" "unit test KO!"
	else
		printf "    \e[32m%s\n\e[m" "unit test OK!"
	fi
}

cd "$(dirname "$0")" || exit

EXIT_CODE=0
for path in $(find . -type f -name "*.c");
do
	echo $path
	gcc -o "minishell" -g -O3 "$path" \
	$(find $REPO_ROOT/srcs/lex/ -type f -name "*.c") \
	$REPO_ROOT/libft/libft/libft.a \
	$REPO_ROOT/libft/libex/libex.a \
	$REPO_ROOT/libft/libhash/libhash.a \
	$REPO_ROOT/libft/libdebug/libdebug.a \
	$SHARED_LIB

	./minishell > output
	AOUT=$?

	if [ $AOUT -ne 0 ]; then
		EXIT_CODE=1
		printf "\e[31m%s\n\e[m" ">> leak KO!"
	else
		printf "\e[32m%s\n\e[m" ">> leak OK!"
	fi
done

cd $REPO_ROOT || exit

make sani-debug &> /dev/null

cd "$(dirname "$0")" || exit

for path in $(find . -type f -name "*.c");
do
	gcc -o "b.out" -g -O3 -fsanitize=address "$path" \
	$(find $REPO_ROOT/srcs/lex/ -type f -name "*.c") \
	$REPO_ROOT/libft/libft/libft.a \
	$REPO_ROOT/libft/libex/libex.a \
	$REPO_ROOT/libft/libhash/libhash.a \
	$REPO_ROOT/libft/libdebug/libdebug.a

	./b.out > output
	BOUT=$?
	if [ $BOUT -ne 0 ]; then
		EXIT_CODE=1
		printf "\e[31m%s\n\e[m" ">> sani KO!"
	else
		printf "\e[32m%s\n\e[m" ">> sani OK!"
	fi
done

diff expect output

if [ $? -ne 0 ]; then
	EXIT_CODE=1
	printf "\e[31m%s\n\e[m" ">> diff KO!"
else
	printf "\e[32m%s\n\e[m" ">> diff OK!"
fi
echo $DIFF

rm ./minishell output
rm ./b.out leaksout
rm -rf ./minishell.dSYM
rm -rf ./b.out.dSYM

cd $REPO_ROOT || exit
make fclean &> /dev/null
make leak &> /dev/null

exit $EXIT_CODE
