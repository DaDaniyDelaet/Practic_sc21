#include <stdio.h>
#define NMAX 10

#define OK 0
#define ERR_IO 1
#define ERR_RANGE 2

int input(int *a, int *n);
void output(int *a, int n);
int max(int *a, int n);
int min(int *a, int n);
double mean(int *a, int n);
double variance(int *a, int n);

void output_result(int max_v, int min_v, double mean_v, double variance_v);

int main() {
    int n, data[NMAX];
    int rc = input(data, &n);
    if (!rc) {
        output(data, n);
        printf("\n");
        output_result(max(data, n), min(data, n), mean(data, n), variance(data, n));
    } else {
        printf("n/a");
    }
    return OK;
}

int input(int *a, int *n) {
    if (scanf("%d", n) != 1) return ERR_IO;
    if (*n <= 0 || n > NMAX) return ERR_RANGE;
    for (int *p = a; p - a < *n; p++) {
        if (scanf("%d", p) != 1) return ERR_IO;
    }
    return OK;
}

void output(int *a, int n) {
    for (int *x = a; x < a + n; x++) {
        printf("%d ", *x);
    }
    // NOTHING
}

int max(int *a, int n) {
    int max = *a;
    for (int *x = a; x < a + n; x++) {
        if (*x > max) max = *x;
    }
    return max;
}

int min(int *a, int n) {
    int min = *a;
    for (int *x = a; x < a + n; x++) {
        if (*x < min) min = *x;
    }
    return min;
}
double mean(int *a, int n) {
    double average = 0;
    for (int *x = a; x < a + n; x++) {
        average += *x;
    }
    return average / n;
}
double variance(int *a, int n) {
    double average = mean(a, n);
    double var = 0;
    for (int *x = a; x < a + n; x++) {
        var += (*x - average) * (*x - average);
    }
    return var;
}

void output_result(int max_v, int min_v, double mean_v, double variance_v) {
    printf("%d %d %.6lf %.6lf", max_v, min_v, mean_v, variance_v);
}
