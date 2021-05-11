#!/bin/bash

set -e

make

export REPO_ROOT=$PWD

for path in $(find ./tests/issue -type f -name test.sh);
	do echo "$path"; bash "$path";
done
