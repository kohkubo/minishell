make fclean > /dev/null

mv srcs/main.c srcs/main.c.orig
cp tests/issue/heredoc_test/main.c srcs/main.c
rm -f srcs/main.o

make &> /dev/null

cp -f ./minishell "$(dirname "$0")"
cd "$(dirname "$0")" || exit

rm -f output leaksout

for file in $(ls *.txt); do
	echo "Testing $file" >> output
	echo "--------------------------------" >> output
	cat $file >> output
	echo "--------------------------------" >> output
	./minishell < $file >> output 2>&1
	echo $? >> output
	echo "--------------------------------" >> output
	echo "" >> output
done

diff expect output
RES=$?

rm -f minishell output

cd $REPO_ROOT || exit

mv srcs/main.c.orig srcs/main.c

rm -f srcs/main.o

exit $RES
