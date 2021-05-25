#!/bin/bash

DIR=$1

make leak

export REPO_ROOT="$PWD"
export SHARED_LIB="$PWD/tests/sharedlib.c"

for path in $(find $DIR -type f -name test.sh);
do
	echo "===== $path ====="
	bash "$path"
	if [ $? -eq 0 ]; then
		printf "\e[32m%s\n\e[m" "OK!"
	else
		printf "\e[31m%s\n\e[m" "KO!"
	fi
done
