#include <stdio.h>

#define OK 0
#define ERR_IO 1

int max(int a, int b) { return a >= b ? a : b; }
int main() {
  int num_1, num_2;

  if (scanf("%d%d", &num_1, &num_2) != 2) {
    printf("n/a");
    return ERR_IO;
  }

  printf("%d", max(num_1, num_2));
  return OK;
}