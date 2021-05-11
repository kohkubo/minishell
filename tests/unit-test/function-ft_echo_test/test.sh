#!/bin/bash

set -e

echo "=============ft_echo================"
cd "$(dirname "$0")" || exit

echo > output
echo aiueo > expect
echo "aiueo test" >> expect
echo -n "aiueo test" >> expect
echo -n >> expect
echo "" >> expect
echo -n "" >> expect
echo >> expect
echo "test" >> expect

gcc test.c $(find $REPO_ROOT/srcs -type f -name echo.c) $REPO_ROOT/libft/libft/libft.a

./a.out
diff expect output
rm expect output a.out
