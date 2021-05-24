#!/bin/bash

# set -e

make

# gcc -shared -fPIC $(dirname $0)/sharedlib.c -o $(dirname $0)/libdestructor.so
# gcc -dynamiclib $(dirname $0)/sharedlib.c -o $(dirname $0)/libdestructor.dylib
# export SHARED_LIB="-L $PWD/tests/unit-test libdestructor.dylib"
export SHARED_LIB="$PWD/tests/unit-test/sharedlib.c"

for path in $(find ./tests/unit-test -type f -name test.sh);
do
	echo "===== $path ====="
	bash "$path"
	if [ $? -eq 0 ]; then
		printf "\e[32m%s\n\e[m" "OK!"
	else
		printf "\e[31m%s\n\e[m" "KO!"
	fi
done
