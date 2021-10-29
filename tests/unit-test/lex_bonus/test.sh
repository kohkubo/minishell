#!/bin/bash

EXIT_CODE=0

DIR="$(dirname "$0")"

EXIT_CODE=0
gcc -g $INCLUDES \
-o "$DIR/a.out" \
"$DIR/main.c" \
"$REPO_ROOT/srcs/utils/get_fullpath.c" \
$REPO_ROOT/srcs/lex/data.c \
$REPO_ROOT/srcs/lex/heredoc.c \
$REPO_ROOT/srcs/lex/lex_bonus.c \
$REPO_ROOT/srcs/lex/store_bonus.c \
$(find $REPO_ROOT/srcs/parse/ -type f -name "*.c") \
$(find $REPO_ROOT/srcs/execute/ -type f -name "*.c") \
$(find $REPO_ROOT/srcs/built-in/ -type f -name "*.c") \
$(find $REPO_ROOT/srcs/expand/ -type f -name "*.c") \
$(find $REPO_ROOT/srcs/signal/ -type f -name "*.c") \
$REPO_ROOT/srcs/env/env.c \
$LIBS -lft -lex -lhash -lreadline -lhistory -L$(brew --prefix readline)/lib -I$(brew --prefix readline)/include $SHARED_LIB || exit

cd "$(dirname "$0")" || exit

rm -rf output leaksout

./a.out > output
diff expect output

if [ $? -ne 0 ]; then
	EXIT_CODE=1
	echo $path
	printf "\e[31m%s\n\e[m" ">> leak KO!"
fi

rm -rf ./a.out output leaksout
rm -rf ./a.out.dSYM

exit $EXIT_CODE
