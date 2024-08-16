#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define OK 0
#define ERR_IO 1
#define ERR_RANGE 2
#define ERR_MEM 3

double det(double **matrix, int m, int n);
int input(double ***matrix, int *m, int *n);
void output(double det);
int matrix_allocate(double ***mat, int m, int n);
void matrix_clear(double ***mat, int *m, int *n);
int main(void) {
    double **matrix = NULL;
    int n, m;

    int rc = input(&matrix, &m, &n);

    if (!rc) {
        output(det(matrix, m, n));
    } else {
        printf("n/a");
    }
    matrix_clear(&matrix, &m, &n);
    return rc;
}
double det(double **mat, int m, int n) {
    double det = 1;
    for (int i = 0; i < m; ++i) {
        double mx = fabs(mat[i][i]);
        int idx = i;
        for (int j = i + 1; j < n; ++j)
            if (mx < fabs(mat[i][j])) mx = fabs(mat[i][idx = j]);
        if (idx != i) {
            for (int j = i; j < n; ++j) {
                double t = mat[j][i];
                mat[j][i] = mat[j][idx];
                mat[j][idx] = t;
            }
            det = -det;
        }
        for (int k = i + 1; k < n; ++k) {
            double t = mat[k][i] / mat[i][i];

            for (int j = i; j < n; ++j) mat[k][j] -= mat[i][j] * t;
        }
    }
    for (int i = 0; i < n; ++i) det *= mat[i][i];
    return det;
}

int input(double ***matrix, int *m, int *n) {
    int rc = OK;
    if (scanf("%d%d", m, n) != 2) {
        rc = ERR_IO;
    } else if (*m <= 0 || *n <= 0 || *m != *n)
        rc = ERR_RANGE;
    if (!rc) {
        rc = matrix_allocate(matrix, *m, *n);
    }
    if (!rc) {
        for (int i = 0; !rc && i < *m; i++) {
            for (int j = 0; !rc && j < *n; j++) {
                if (scanf("%lf", &(*matrix)[i][j]) != 1) {
                    rc = ERR_IO;
                }
            }
        }
    }
    return rc;
}

int matrix_allocate(double ***mat, int m, int n) {
    int rc = OK;
    double **ptr = malloc(m * sizeof(double *) + m * n * sizeof(double));
    if (ptr) {
        for (int i = 0; i < m; i++) {
            ptr[i] = (double *)(ptr + m) + i * n;
        }
        *mat = ptr;
    } else {
        rc = ERR_MEM;
    }
    return rc;
}

void matrix_clear(double ***mat, int *m, int *n) {
    if (*mat) {
        free(*mat);
        *mat = NULL;
    }
    *m = 0;
    *n = 0;
}

void output(double det) { printf("%.6lf", det); }
