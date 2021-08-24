gcc foo1.c bar1.c

# 同じ strong symbol が2つあるため、エラーになる
# duplicate symbol '_main' in:
#     /var/folders/9y/135njlnd0h76kc41c3bvlc080000gn/T/foo1-d6fde8.o
#     /var/folders/9y/135njlnd0h76kc41c3bvlc080000gn/T/bar1-279437.o
# ld: 1 duplicate symbol for architecture x86_64
# clang: error: linker command failed with exit code 1 (use -v to see invocation)
