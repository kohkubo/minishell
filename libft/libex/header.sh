#!/bin/zsh -x

NAME_H=$1
MAKE_PATH=$2

CURDIR=$PWD

# header make

sed -i '' -E "/^(int|void|size_t|t_.*|char|float|double|struct|unsigned|short|const|long|bool|signed).*;$/d" ${NAME_H}
sed -i '' -e '/#endif/d'  ${NAME_H}
sed -i '' -E '/^$/d'  ${NAME_H}

prot=$(find . -type f -name '*.c' | xargs cat | sed -e '/^[a-zA-Z].*)$/!d' -e '/^static/d' -e "s/)$/);/g")
TABS=$(echo "${prot}" | awk '{sub("[\t ][\t ]*\\**[a-zA-Z_0-9][a-zA-Z_0-9]*\\(.*", "");print length($0)}' |
		sort -nr | head -n 1 | xargs -I{} expr {} / 4 + 1)
header="
$(echo "${prot}" |
	awk -v tabs=${TABS} '
	{
		s = $0;
		sub("[\t ][\t ]*\\**[a-zA-Z_0-9][a-zA-Z_0-9]*\\(.*", "");
		t = "";
		l = tabs - int(length($0) / 4);
		for (i = 0; i < l; i++)
			t=t"\t";
		str = substr(s, length($0) + 1, index(s, ";"))
		sub("[\t ][\t ]*", t, str);
		print $0 str
	}')
"

echo "${header}" | sort -u >> ${NAME_H}
sed -i '' -e '/\main(void);/d' ${NAME_H}

echo '#endif' >> ${NAME_H}

# Makefile

sed -i '' -e '/^\t\./d' "${MAKE_PATH}"
sed -i '' -e 's/src =\\/src =/g' "${MAKE_PATH}"

# cd "${DIR}" || exit

srcs=$(find . -type f -name '*.c' | sed -e 's/^/\t/g' -e 's/$/\\/g' | sort -u)

cd ${CURDIR}

sed -i '' -E "s|^src =|src =\\n\"${srcs}\"|" "${MAKE_PATH}"
sed -i '' -e 's/src =/src =\\/' -e 's/c"$/c/' -e 's/^"//' "${MAKE_PATH}"
sed -i '' -E 's/^(\t.*)\.c$/\1\.c \\/' "${MAKE_PATH}"
