#include <stdio.h>
#include <stdlib.h>
#define OK 0
#define ERR_IO 1
#define ERR_RANGE 2
#define ERR_MEM 3

int matrix_allocate(int ***mat, int m, int n);

void matrix_clear(int ***mat, int *m, int *n);

/*
    1 6 7
    2 5 8
    3 4 9
*/
void sort_vertical(int **matrix, int m, int n, int **result_matrix);

/*
    1 2 3
    6 5 4
    7 8 9
*/
void sort_horizontal(int **matrix, int m, int n, int **result_matrix);

int input(int ***matrix, int *m, int *n);
void output(int **matrix, int m, int n);

int main(void) {
    int **matrix = NULL, **result = NULL;
    int n, m;
    int rm, rn;

    int rc = input(&matrix, &m, &n);
    if (!rc) {
        rm = m;
        rn = n;
        rc = matrix_allocate(&result, rm, rn);
    }

    if (!rc) {
        sort_vertical(matrix, m, n, result);
        output(result, m, n);
        printf("\n\n");

        sort_horizontal(matrix, m, n, result);
        output(result, m, n);
    } else {
        printf("n/a");
    }
    matrix_clear(&matrix, &m, &n);
    matrix_clear(&result, &rm, &rn);
    return rc;
}

int input(int ***matrix, int *m, int *n) {
    int rc = OK;
    if (scanf("%d%d", m, n) != 2) {
        rc = ERR_IO;
    } else if (*m <= 0 || *n <= 0)
        rc = ERR_RANGE;
    if (!rc) {
        rc = matrix_allocate(matrix, *m, *n);
    }
    if (!rc) {
        for (int i = 0; !rc && i < *m; i++) {
            for (int j = 0; !rc && j < *n; j++) {
                if (scanf("%d", &(*matrix)[i][j]) != 1) {
                    rc = ERR_IO;
                }
            }
        }
    }
    return rc;
}

int matrix_allocate(int ***mat, int m, int n) {
    int rc = OK;
    int **ptr = malloc(m * sizeof(int *) + m * n * sizeof(int));
    if (ptr) {
        for (int i = 0; i < m; i++) {
            ptr[i] = (int *)(ptr + m) + i * n;
        }
        *mat = ptr;
    } else {
        rc = ERR_MEM;
    }
    return rc;
}

void matrix_clear(int ***mat, int *m, int *n) {
    if (*mat) {
        free(*mat);
        *mat = NULL;
    }
    *m = 0;
    *n = 0;
}

void output(int **matrix, int m, int n) {
    for (int i = 0; i < m - 1; i++) {
        for (int j = 0; j < n - 1; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("%d\n", matrix[i][n - 1]);
    }
    for (int j = 0; j < n - 1; j++) {
        printf("%d ", matrix[m - 1][j]);
    }
    printf("%d", matrix[m - 1][n - 1]);
}

void swap(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}

void get_vertical_min(int **matrix, int m, int n, int start_i, int start_j, int start_direction, int *fm,
                      int *fn) {
    int min_value = matrix[start_i][start_j];
    *fm = start_i;
    *fn = start_j;

    int i = start_i;
    int j = start_j;
    int direction = start_direction;

    while (j < n) {
        while (i >= 0 && i < m) {
            if (matrix[i][j] < min_value) {
                min_value = matrix[i][j];
                *fm = i;
                *fn = j;
            }
            i += direction;
        }
        direction *= -1;
        i += direction;
        j++;
    }
}

void sort_vertical(int **matrix, int m, int n, int **result_matrix) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            result_matrix[i][j] = matrix[i][j];
        }
    }

    int i = 0;
    int j = 0;
    int direction = 1;

    while (j < n) {
        while (i >= 0 && i < m) {
            int fm, fn;
            get_vertical_min(result_matrix, m, n, i, j, direction, &fm, &fn);
            swap(&result_matrix[i][j], &result_matrix[fm][fn]);
            i += direction;
        }
        direction *= -1;
        i += direction;
        j++;
    }
}

void get_horizontal_min(int **matrix, int m, int n, int start_i, int start_j, int start_direction, int *fm,
                        int *fn) {
    int min_value = matrix[start_i][start_j];
    *fm = start_i;
    *fn = start_j;

    int i = start_i;
    int j = start_j;
    int direction = start_direction;

    while (i < m) {
        while (j >= 0 && j < n) {
            if (matrix[i][j] < min_value) {
                min_value = matrix[i][j];
                *fm = i;
                *fn = j;
            }
            j += direction;
        }
        direction *= -1;
        j += direction;
        i++;
    }
}

void sort_horizontal(int **matrix, int m, int n, int **result_matrix) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            result_matrix[i][j] = matrix[i][j];
        }
    }

    int i = 0;
    int j = 0;
    int direction = 1;

    while (i < m) {
        while (j >= 0 && j < n) {
            int fm, fn;
            get_horizontal_min(result_matrix, m, n, i, j, direction, &fm, &fn);
            swap(&result_matrix[i][j], &result_matrix[fm][fn]);
            j += direction;
        }
        direction *= -1;
        j += direction;
        i++;
    }
}
