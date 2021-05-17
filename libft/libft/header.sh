#!/bin/bash

cd "$(dirname $0)" || exit
NAME_H=libft.h

prot=$(cat *.c | sed -e '/^[a-zA-Z].*)$/!d' -e '/^static/d' -e "s/)$/);/g")
TABS=$(echo "${prot}" | sed 's/\t.*//g' | awk '{print length($0)}' | sort -nr | head -n 1 | xargs -I{} expr {} / 4 + 1)

header="$(sed -e "/^[a-zA-Z][a-zA-Z_0-9]*.*);$/d" -e '/#endif/d' -e '/^$/d' ${NAME_H})
$(echo "${prot}" | awk -v tabs=${TABS} '{s=$0; sub("\t.*", ""); l=tabs - int(length($0) / 4); t="";for(i=0;i<l;i++){t=t "\t"};sub("\t\t*", t, s); print s}')
#endif"

echo "${header}" > ${NAME_H}

sed -i '' -e '/^\t\./d' Makefile
sed -i '' -e 's/src =\\/src =/g' Makefile
srcs=$(find . -type f -name '*.c' | sed -e 's/^/\t/g' -e 's/$/\\/g')
sed -i '' -E "s|^src =|src =\\n\"${srcs}\"|" Makefile
sed -i '' -e 's/src =/src =\\/' -e 's/"//' Makefile
sed -i '' -e 's/\.c$/\.c \\/' Makefile
