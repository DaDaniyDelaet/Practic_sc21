#include <math.h>
#include <stdio.h>

#define OK 0
#define ERR_IO 1
#define ERR_RANGE 2

int fib(int n, int a, int b) {
  if (n == 1) {
    return a;
  } else if (n > 2)
    return fib(n - 1, b, a + b);
  else if (n == 2) {
    return b;
  } else {
    return -1;
  }
}

int main() {
  int n = 0;
  if (scanf("%d", &n) != 1) {
    printf("n/a");
    return ERR_IO;
  } else if (n <= 0) {
    printf("n/a");
    return ERR_RANGE;
  }

  printf("%d", fib(n, 1, 1));
}