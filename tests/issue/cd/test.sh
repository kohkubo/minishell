#!/bin/bash


cp ./minishell "$(dirname "$0")"

cd "$(dirname "$0")" || exit

echo $PWD
dirname=$PWD

rm -rf expect output leaksout

for file in $(ls *.txt); do
	mkdir -p ./testcd1/testcd2/testcd3
	mkdir -p ./testcd4/testcd5/testcd6
	echo "aaa" > ./testcd4/testcd5/testcd6/test00.txt
	echo "bbb" > ./testcd4/testcd5/testcd6/test01.txt
	echo "ccc" > ./testcd4/testcd5/testcd6/test02.txt
	echo "Testing $file"
	bash < $file >> expect 2>&1
	./minishell < $file >> output 2>&1
	sed -i "" -e "/minishell> /d" output
	sed -i "" -e "/cd: error /d" output
	diff expect output &> /dev/null
	sed -i "" -e "/cd: error /d" expect
	if [ $? -ne 0 ]; then
		echo "FAIL: $file"
		cat $file
		diff expect output -y -W 180
		RES=1
		exit 1
	fi
	cd $dirname
	rm -rf output expect testcd1 testcd4
done

rm -f a.out leaksout minishell
rm -rf a.out.dSYM

exit $RES
