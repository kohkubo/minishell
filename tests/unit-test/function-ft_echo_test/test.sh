#!/bin/bash

set -e

echo "=============ft_echo================"
cd "$(dirname "$0")" || exit

gcc test.c $(find $REPO_ROOT/srcs -type f -name echo.c) $REPO_ROOT/libft/libft/libft.a
./a.out
