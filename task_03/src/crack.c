#include <math.h>
#include <stdio.h>

#define OK 0
#define ERR_IO 1
#define ERR_RANGE 2

#define EPS 1e-6

int check(double x, double y) { return pow(x, 2) + pow(y, 2) <= 25; }
int main() {
  double x, y;
  if (scanf("%lf%lf", &x, &y) != 2) {
    return ERR_IO;
  }

  int res = check(x, y);
  if (res)
    printf("GOTCHA");
  else
    printf("MISS");
  return OK;
}