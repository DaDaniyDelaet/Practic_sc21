#include <math.h>
#include <stdio.h>

#define STEPS 42

int check_anesy(double x) {
  (void)x;
  return 1;
}
double anesy(double x) { return 1 / (1 + x * x); }

int check_bernulli(double x) { return (sqrt(1 + 4 * x * x) - x * x - 1) >= 0; }
double bernulli(double x) { return sqrt(sqrt(1 + 4 * x * x) - x * x - 1); }

int check_gip(double x) { return x != 0; }
double gip(double x) { return 1 / (x * x); }

int main() {
  double x = -M_PI;
  double step = 2 * M_PI / (STEPS - 1);
  for (int i = 0; i < STEPS; i++) {
    printf("%.7lf |", x);

    if (check_anesy(x)) {
      printf(" %.7lf |", anesy(x));
    } else {
      printf(" - |");
    }

    if (check_bernulli(x)) {
      printf(" %.7lf |", bernulli(x));
    } else {
      printf(" - |");
    }

    if (check_gip(x)) {
      printf(" %.7lf\n", gip(x));
    } else {
      printf(" -\n");
    }
    x += step;
  }
}