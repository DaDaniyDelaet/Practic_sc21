#include <math.h>
#include <stdio.h>

#define OK 0
#define ERR_IO 1
#define ERR_RANGE 2

double func(double x) {
  return 7e-3 * pow(x, 4) +
         ((22.8 * pow(x, 1.0 / 3) - 1e3) * x + 3) / (x * x / 2.0) -
         x * pow((10 + x), (2.0 / x)) - 1.01;
}

int main() {
  double num;

  if (scanf("%lf", &num) != 1) return ERR_IO;

  if (num == 0) {
    printf("n/a");
    return ERR_RANGE;
  }

  printf("%.1lf", func(num));
  return OK;
}