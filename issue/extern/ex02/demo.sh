gcc foo2.c bar2.c

# 同じ strong symbol が2つあるため、エラーになる
# duplicate symbol '_x' in:
#     /var/folders/9y/135njlnd0h76kc41c3bvlc080000gn/T/foo2-58969e.o
#     /var/folders/9y/135njlnd0h76kc41c3bvlc080000gn/T/bar2-317719.o
# ld: 1 duplicate symbol for architecture x86_64
# clang: error: linker command failed with exit code 1 (use -v to see invocation)
