DIR="$(dirname "$0")"

RES=0

gcc $REPO_ROOT/libft/libex/ft_atol.c $REPO_ROOT/libft/libex/ft_isspace.c $REPO_ROOT/libft/libft/ft_isdigit.c $DIR/main.c $SHARED_LIB

./a.out
RES=$?

rm -rf a.out leaksout
exit $RES
