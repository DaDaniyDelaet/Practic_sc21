#include <stdio.h>

#define OK 0
#define ERR_IO 1
int main() {
  int name;

  if (scanf("%d", &name) != 1) return ERR_IO;

  printf("Hello, %d!", name);
  return OK;
}