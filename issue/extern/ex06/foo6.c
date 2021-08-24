/* foo.c */
#include <stdio.h>
#include "foo.h"

int x = 100;

int main()
{
	printf("x = %d\n", x);
	f();
	printf("x = %d\n", x);
	return 0;
}
