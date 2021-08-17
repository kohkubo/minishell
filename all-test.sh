#!/bin/bash

DIR=$1
if [ "$2" != "" ]; then
	DIR="$1/$2"
fi

export REPO_ROOT="$PWD"
export INCLUDES="-I./includes -I./libft/libft -I./libft/libex -I./libft/libhash -I./libft/libdebug"
export LIBS="-L./libft/libft -L./libft/libex -L./libft/libhash -L./libft/libdebug"
export SHARED_LIB="$PWD/tests/sharedlib.c"

FLG=0

make fclean > /dev/null
make leak > /dev/null

for path in $(find $DIR -type f -name test.sh);
do
	echo "===== $path ====="
	bash "$path"
	if [ $? -eq 0 ]; then
		printf "\e[32m%s\n\e[m" "OK!"
	else
		printf "\e[31m%s\n\e[m" "KO!"
		FLG=1
	fi
done

exit $FLG
