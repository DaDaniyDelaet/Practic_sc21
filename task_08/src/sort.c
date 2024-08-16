#include <stdio.h>
#include <stdlib.h>
#define NMAX 10

#define OK 0
#define ERR_IO 1
#define ERR_RANGE 2

int input(int **a, int *n);
void output(const int *a, int n);
void sort(int *a, int n);

int main() {
    int *data = NULL, n;
    int rc = OK;
    rc = input(&data, &n);
    if (!rc) {
        sort(data, n);
        output(data, n);
    } else {
        printf("n/a");
    }
    if (data) {
        free(data);
        data = NULL;
    }

    return rc;
}

int input(int **a, int *n) {
    int rc = OK;
    if (scanf("%d", n) != 1) rc = ERR_IO;
    if (!rc && *n <= 0) rc = ERR_RANGE;
    if (!rc) *a = calloc(*n, sizeof(int));
    for (int *p = *a; !rc && p - *a < *n; p++) {
        if (scanf("%d", p) != 1) rc = ERR_IO;
    }
    return rc;
}

void output(const int *a, int n) {
    for (const int *x = a; x < a + n; x++) {
        printf("%d", *x);
        if (x != a + n - 1) printf(" ");
    }
}

void swap(int *xp, int *yp) {
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void sort(int *arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        int swapped = 0;
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(&arr[j], &arr[j + 1]);
                swapped = 1;
            }
        }
        if (swapped == 0) break;
    }
}
