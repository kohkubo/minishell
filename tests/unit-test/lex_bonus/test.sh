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


rm -rf $DIR/output $DIR/leaksout

$DIR/a.out > $DIR/output
diff $DIR/expect $DIR/output

if [ $? -ne 0 ]; then
	EXIT_CODE=1
	echo $path
	printf "\e[31m%s\n\e[m" ">> leak KO!"
fi

rm -rf $DIR/a.out $DIR/output $DIR/leaksout
rm -rf $DIR/a.out.dSYM

exit $EXIT_CODE
