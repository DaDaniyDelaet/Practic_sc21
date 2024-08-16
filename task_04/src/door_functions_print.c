#include <math.h>
#include <stdio.h>

#define STEPS 42
#define X_POINTS 42
#define Y_POINTS 21

int check_anesy(double x) {
  (void)x;
  return 1;
}
double anesy(double x) { return 1 / (1 + x * x); }

int check_bernulli(double x) { return (sqrt(1 + 4 * x * x) - x * x - 1) >= 0; }
double bernulli(double x) { return sqrt(sqrt(1 + 4 * x * x) - x * x - 1); }

int check_gip(double x) { return x != 0; }
double gip(double x) { return 1 / (x * x); }

double get_min_y() {
  double min_y = 0;
  int flag = 0;
  double x = -M_PI;
  double step = 2 * M_PI / (STEPS - 1);

  for (int i = 0; i < STEPS; i++) {
    if (!flag) {
      if (check_anesy(x)) {
        min_y = anesy(x);
      } else if (check_bernulli(x)) {
        min_y = bernulli(x);
      } else if (check_gip(x)) {
        min_y = gip(x);
      }
    } else {
      if (check_anesy(x)) {
        min_y = fmin(anesy(x), min_y);
      } else if (check_bernulli(x)) {
        min_y = fmin(bernulli(x), min_y);
      } else if (check_gip(x)) {
        min_y = fmin(gip(x), min_y);
      }
    }
    x += step;
  }
  return min_y;
}

double get_max_y() {
  double max_y = 0;
  int flag = 0;
  double x = -M_PI;
  double step = 2 * M_PI / (X_POINTS - 1);

  for (int i = 0; i < X_POINTS; i++) {
    if (!flag) {
      if (check_anesy(x)) {
        max_y = anesy(x);
      } else if (check_bernulli(x)) {
        max_y = bernulli(x);
      } else if (check_gip(x)) {
        max_y = gip(x);
      }
      flag = !flag;
    } else {
      if (check_anesy(x)) {
        max_y = fmax(anesy(x), max_y);
      } else if (check_bernulli(x)) {
        max_y = fmax(bernulli(x), max_y);
      } else if (check_gip(x)) {
        max_y = fmax(gip(x), max_y);
      }
    }
    x += step;
  }
  return max_y;
}

void print_funcs(double min_y, double max_y) {
  double x = -M_PI;
  double step = 2 * M_PI / (STEPS - 1);
  double delta = max_y - min_y;

  for (int i = 0; i < STEPS; i++) {
    int anesy_y = -1, bernulli_y = -1, gip_y = -1;
    if (check_anesy(x)) {
      anesy_y = round(anesy(x) / delta * Y_POINTS);
    }
    if (check_bernulli(x)) {
      bernulli_y = round(bernulli(x) / delta * Y_POINTS);
    }
    if (check_gip(x)) {
      gip_y = round(gip(x) / delta * Y_POINTS);
    }
    for (int j = 0; j < Y_POINTS; j++) {
      if (j == anesy_y)
        printf("*");
      else if (j == bernulli_y)
        printf("*");
      else if (j == gip_y)
        printf("*");
      else
        printf(" ");
    }
    printf("\n");
    x += step;
  }
}

int main() {
  double min_y = get_min_y();
  double max_y = get_max_y();
  print_funcs(min_y, max_y);
}