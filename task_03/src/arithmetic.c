#include <stdio.h>

#define OK 0
#define ERR_IO 1
#define ERR_RANGE 2

int main() {
  double inp_1, inp_2;
  int num_1, num_2;

  if (scanf("%lf%lf", &inp_1, &inp_2) != 2) {
    printf("n/a");
    return ERR_IO;
  }

  num_1 = inp_1;
  num_2 = inp_2;

  if (inp_1 != num_1) {
    printf("n/a");
    return ERR_RANGE;
  } else if (inp_2 != num_2) {
    printf("n/a");
    return ERR_RANGE;
  }

  printf("%d ", num_1 + num_2);
  printf("%d ", num_1 - num_2);
  printf("%d ", num_1 * num_2);

  if (num_2 != 0)
    printf("%d", num_1 / num_2);
  else
    printf("n/a");

  return 0;
}