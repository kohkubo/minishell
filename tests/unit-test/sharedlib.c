#include <stdlib.h>
#include <stdio.h>

__attribute__((destructor))
void destructor()
{
  int status;

  status = system("leaks a.out &> leaksout");
  if (status) {
    printf("leak!!!\n");
    system("cat leaksout");
    exit(1);
  }
}
