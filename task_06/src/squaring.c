#include <stdio.h>
#define NMAX 10

#define OK 0
#define ERR_IO 1
#define ERR_RANGE 2
int input(int *a, int *n);
void output(int *a, int n);
void squaring(int *a, int n);

int main() {
    int n, data[NMAX];
    int rc = OK;
    rc = input(data, &n);
    if (!rc) {
        squaring(data, n);
        output(data, n);
    } else {
        printf("n/a");
    }

    return rc;
}

int input(int *a, int *n) {
    int rc = OK;
    if (scanf("%d", n) != 1) rc = ERR_IO;
    if (!rc && (*n <= 0 || *n > NMAX)) rc = ERR_RANGE;
    for (int *p = a; !rc && p - a < *n; p++) {
        if (scanf("%d", p) != 1) rc = ERR_IO;
    }
    return rc;
}

void output(int *a, int n) {
    for (int *x = a; x < a + n; x++) {
        printf("%d ", *x);
    }
}

void squaring(int *a, int n) {
    for (int *x = a; x < a + n; x++) {
        *x = (*x) * (*x);
    }
}
