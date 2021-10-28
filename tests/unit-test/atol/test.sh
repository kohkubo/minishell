DIR="$(dirname "$0")"

gcc $REPO_ROOT/libft/libex/ft_atol.c $REPO_ROOT/libft/libex/ft_isspace.c $REPO_ROOT/libft/libft/ft_isdigit.c $DIR/main.c

./a.out
exit $?
