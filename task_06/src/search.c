/*
    Search module for the desired value from data array.

    Returned value must be:
        - "even"
        - ">= mean"
        - "<= mean + 3 * sqrt(variance)"
        - "!= 0"

        OR

        0
*/
#include <math.h>
#include <stdio.h>
#define NMAX 30

#define OK 0
#define ERR_IO 1
#define ERR_RANGE 2

int input(int *a, int *n);
void output(int *a, int n);
double mean(int *a, int n);
double variance(int *a, int n);
int search(int *a, int n);

void output_result(int res);

int main() {
    int n, data[NMAX];

    int rc = input(data, &n);
    if (!rc) {
        int res = search(data, n);
        output_result(res);
    } else {
        printf("n/a");
    }
    return OK;
}

int input(int *a, int *n) {
    if (scanf("%d", n) != 1) return ERR_IO;
    if (*n <= 0) return ERR_RANGE;
    for (int *p = a; p - a < *n; p++) {
        if (scanf("%d", p) != 1) return ERR_IO;
    }
    return OK;
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

int search(int *a, int n) {
    int res = 0;
    double mn = mean(a, n);
    double var = variance(a, n);
    for (int *x = a; x < a + n; x++) {
        if (*x % 2 == 0 && *x >= mn && *x <= mn + 3 * sqrt(var) && *x != 0) {
            res = *x;
            break;
        }
    }
    return res;
}

void output_result(int res) { printf("%d", res); }
