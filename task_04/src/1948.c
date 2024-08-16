#include <math.h>
#include <stdio.h>

#define OK 0
#define ERR_IO 1
#define ERR_RANGE 2

int isSimple(int a) {
  for (int i = 2; i < a; i++) {
    int tmp = a;
    while (tmp > 0) {
      tmp -= i;
    }
    if (tmp == 0) {
      return 0;
    }
  }
  return 1;
}

int getMaxSimpleDevider(int a) {
  if (a < 0) a = -a;
  int max_delim = -1;
  for (int i = 1; i <= a; i++) {
    if (isSimple(i)) {
      int tmp = a;
      while (tmp > 0) tmp -= i;
      if (tmp == 0) max_delim = i;
    }
  }
  return max_delim;
}

int main() {
  int a;
  if (scanf("%d", &a) != 1) {
    printf("n/a");
    return ERR_IO;
  }
  int max_del = getMaxSimpleDevider(a);
  if (max_del == -1)
    printf("n/a");
  else
    printf("%d", max_del);
  return OK;
}