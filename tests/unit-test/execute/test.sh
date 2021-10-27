DIR="$(dirname "$0")"

RES=0
gcc -g $INCLUDES \
-o "$DIR/a.out" \
"$DIR/test.c" \
"$REPO_ROOT/srcs/utils/get_fullpath.c" \
"$REPO_ROOT/srcs/parse/astree.c" \
$(find $REPO_ROOT/srcs/execute/ -type f -name "*.c") \
$(find $REPO_ROOT/srcs/built-in/ -type f -name "*.c") \
$(find $REPO_ROOT/srcs/signal/ -type f -name "*.c") \
$REPO_ROOT/srcs/env/env.c \
$LIBS -lft -lex -lhash -lreadline -lhistory -L$(brew --prefix readline)/lib -I$(brew --prefix readline)/include $SHARED_LIB || exit 1

cd $DIR

./a.out
if [ $? -eq 0 ]; then
	printf "\e[32m%s\n\e[m" ">> OK"
else
	RES=1
	printf "\e[31m%s\n\e[m" ">> KO"
fi

rm -f expect out leaksout a.out
rm -rf a.out.dSYM

cd - > /dev/null

exit $RES
