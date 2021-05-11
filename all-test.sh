#!/bin/bash

set -e

make

for path in $(find ./tests -type f -name test.sh);
	do echo "$path"; bash "$path";
done
