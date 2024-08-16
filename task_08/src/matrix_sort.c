#include <stdio.h>
#include <stdlib.h>

#define OK 0
#define ERR_IO 1
#define ERR_RANGE 2
#define ERR_MEM 3

#define MAXN 100

int matrix_allocate_1(int ***matrix, int m, int n);
int matrix_allocate_2(int ***matrix, int m, int n);
int matrix_allocate_3(int ***matrix, int m, int n);

void matrix_free_1(int ***matrix, int m, int n);
void matrix_free_2(int ***matrix, int m, int n);
void matrix_free_3(int ***matrix, int m, int n);

int matrix_input(int **matrix, int m, int n);
void matrix_output(const int **matrix, int m, int n);

int array_summ(const int *arr, int n);

void sort(int **mat, int m, int n);

int main(void) {
    int rc = OK;
    int mode;
    int m, n;
    int **mat = NULL;

    if (scanf("%d", &mode) != 1) rc = ERR_IO;
    if (!rc && (mode <= 0 || mode > 3)) rc = ERR_RANGE;
    if (!rc && scanf("%d%d", &m, &n) != 2) rc = ERR_IO;
    if (!rc && ((n <= 0 || m <= 0))) rc = ERR_RANGE;
    if (!rc) {
        if (mode == 1)
            rc = matrix_allocate_1(&mat, m, n);
        else if (mode == 2)
            rc = matrix_allocate_2(&mat, m, n);
        else if (mode == 3)
            rc = matrix_allocate_3(&mat, m, n);
    }
    if (!rc) {
        rc = matrix_input(mat, m, n);
    }
    if (!rc) {
        sort(mat, m, n);
        matrix_output((const int **)mat, m, n);
    }
    if (mode == 1)
        matrix_free_1(&mat, m, n);
    else if (mode == 2)
        matrix_free_2(&mat, m, n);
    else if (mode == 3)
        matrix_free_3(&mat, m, n);
    if (rc) printf("n/a");
    return rc;
}

int matrix_allocate_1(int ***matrix, int m, int n) {
    int **single_array_matrix = malloc(m * n * sizeof(int) + m * sizeof(int *));
    int rc = OK;
    if (!single_array_matrix) rc = ERR_MEM;
    if (!rc) {
        int *ptr = (int *)(single_array_matrix + m);
        if (!ptr) rc = ERR_MEM;
        for (int i = 0; !rc && i < m; i++) single_array_matrix[i] = ptr + n * i;
    }
    if (!rc)
        *matrix = single_array_matrix;
    else
        matrix_free_1(&single_array_matrix, m, n);
    return rc;
}

void matrix_free_1(int ***matrix, int m, int n) {
    (void)n;
    (void)m;
    if (*matrix) {
        free(*matrix);
        *matrix = NULL;
    }
}

int matrix_allocate_2(int ***matrix, int m, int n) {
    int rc = OK;
    int **pointer_array = malloc(m * sizeof(int *));
    if (!pointer_array) rc = ERR_MEM;
    for (int i = 0; !rc && i < m; i++) {
        pointer_array[i] = malloc(n * sizeof(int));
        if (!pointer_array[i]) rc = ERR_MEM;
    }
    if (rc)
        matrix_free_2(matrix, m, n);
    else
        *matrix = pointer_array;
    return rc;
}

void matrix_free_2(int ***matrix, int m, int n) {
    (void)n;
    if (*matrix != NULL) {
        for (int i = 0; i < m; i++) {
            if ((*matrix)[i]) {
                free((*matrix)[i]);
                (*matrix)[i] = 0;
            }
        }
        free(*matrix);
        *matrix = 0;
    }
}

int matrix_allocate_3(int ***matrix, int m, int n) {
    int **pointer_array = malloc(m * sizeof(int *));
    int *values_array = malloc(m * n * sizeof(int));
    int rc = OK;
    if (!values_array || !pointer_array) {
        rc = ERR_MEM;
    }
    for (int i = 0; !rc && i < m; i++) {
        pointer_array[i] = values_array + n * i;
        if (!pointer_array[i]) rc = ERR_MEM;
    }
    if (rc)
        matrix_free_3(matrix, m, n);
    else
        *matrix = pointer_array;
    return rc;
}

void matrix_free_3(int ***matrix, int m, int n) {
    (void)m;
    (void)n;
    if (*matrix) {
        int *ptr = (*matrix)[0];
        for (int i = 0; i < m; i++) {
            if ((*matrix)[i] != NULL && (*matrix)[i] < ptr) ptr = (*matrix)[i];
        }
        if (ptr) free(ptr);
        free(*matrix);
    }
    *matrix = NULL;
}

void matrix_output(const int **matrix, int m, int n) {
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

int matrix_input(int **matrix, int m, int n) {
    int rc = OK;
    for (int i = 0; !rc && i < m; i++) {
        for (int j = 0; !rc && j < n; j++) {
            if (scanf("%d", &matrix[i][j]) != 1) rc = ERR_IO;
        }
    }
    return rc;
}

void swap(int **xp, int **yp) {
    int *temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void sort(int **mat, int m, int n) {
    for (int i = 0; i < m - 1; i++) {
        int swapped = 0;
        for (int j = 0; j < m - i - 1; j++) {
            if (array_summ(mat[j], n) > array_summ(mat[j + 1], n)) {
                swap(&mat[j], &mat[j + 1]);
                swapped = 1;
            }
        }
        if (swapped == 0) break;
    }
}

int array_summ(const int *arr, int n) {
    int summ = 0;
    for (const int *p = arr; p < arr + n; p++) {
        summ += *p;
    }
    return summ;
}
