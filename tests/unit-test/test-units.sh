#!/bin/bash

# set -e

make

export REPO_ROOT=$PWD

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
