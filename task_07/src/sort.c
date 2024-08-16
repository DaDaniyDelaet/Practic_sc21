#include <stdio.h>
#define NMAX 10

#define OK 0
#define ERR_IO 1
#define ERR_RANGE 2

int input(int *a);
void output(int *a);
void sort(int *a);

int main() {
    int data[NMAX];
    int rc = OK;
    rc = input(data);
    if (!rc) {
        sort(data);
        output(data);
    } else {
        printf("n/a");
    }

    return rc;
}

int input(int *a) {
    int rc = OK;
    for (int *p = a; !rc && p - a < NMAX; p++) {
        if (scanf("%d", p) != 1) rc = ERR_IO;
    }
    return rc;
}

void output(int *a) {
    for (int *x = a; x < a + NMAX; x++) {
        printf("%d", *x);
        if (x < a + NMAX - 1) printf(" ");
    }
}

void swap(int *xp, int *yp) {
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void sort(int *arr) {
    for (int i = 0; i < NMAX - 1; i++) {
        int swapped = 0;
        for (int j = 0; j < NMAX - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(&arr[j], &arr[j + 1]);
                swapped = 1;
            }
        }
        if (swapped == 0) break;
    }
}
