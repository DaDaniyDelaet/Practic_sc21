#include <stdio.h>
#define NMAX 10

#define OK 0
#define ERR_IO 1
#define ERR_RANGE 2

int input(int *a, int *n);
void output(int *a, int n);
void cycle_shift(int *a, int n, int delta);

int main() {
    int n, data[NMAX], delta;
    int rc = OK;
    rc = input(data, &n);
    if (!rc && scanf("%d", &delta) != 1) {
        rc = ERR_IO;
    }
    if (!rc) {
        cycle_shift(data, n, delta);
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
        printf("%d", *x);
        if (x < a + n - 1) printf(" ");
    }
}

void cycle_shift(int *a, int n, int delta) {
    if (n > 0) {
        if (delta < 0) {
            while (delta++ < 0) {
                int cur = a[n - 1];
                for (int i = n - 1; i > 0; i--) {
                    a[i] = a[i - 1];
                }
                a[0] = cur;
            }
        } else {
            while (delta-- > 0) {
                int first = a[0];
                for (int i = 1; i < n; i++) {
                    a[i - 1] = a[i];
                }
                a[n - 1] = first;
            }
        }
    }
}
