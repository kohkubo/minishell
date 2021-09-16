#!/bin/bash

EXIT_CODE=0

make -j8 tests/unit-test/function-lex/main.c+leak > /dev/null

cd "$(dirname "$0")" || exit

./a.out > output
diff expect output

if [ $? -ne 0 ]; then
	EXIT_CODE=1
	echo $path
	printf "\e[31m%s\n\e[m" ">> leak KO!"
fi

cd "$REPO_ROOT" || exit
make -j8 tests/unit-test/function-lex/main.c+sani > /dev/null
cd "$(dirname "$0")" || exit

./a.out > output
diff expect output

if [ $? -ne 0 ]; then
	EXIT_CODE=1
	printf "\e[31m%s\n\e[m" ">> diff KO!"
fi
echo $DIFF

rm ./a.out output leaksout
rm -rf ./a.out.dSYM

cd "$REPO_ROOT" || exit
make fclean >/dev/null
make -j8 leak > /dev/null

exit $EXIT_CODE
