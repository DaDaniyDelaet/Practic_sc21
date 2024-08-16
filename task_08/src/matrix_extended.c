#include <stdio.h>
#include <stdlib.h>

#define OK 0
#define ERR_IO 1
#define ERR_RANGE 2
#define ERR_MEM 3

#define MAXN 100

int matrix_allocate_2(int ***matrix, int m, int n);
int matrix_allocate_3(int ***matrix, int m, int n);
int matrix_allocate_4(int ***matrix, int m, int n);

void matrix_free_2(int ***matrix, int m, int n);
void matrix_free_3(int ***matrix, int m, int n);
void matrix_free_4(int ***matrix, int m, int n);

int matrix_input(int **matrix, int m, int n);
int static_matrix_input(int matrix[MAXN][MAXN], int m, int n);
void matrix_output(const int **matrix, int m, int n);
void static_matrix_output(int matrix[MAXN][MAXN], int m, int n);

int array_allocate(int **arr, int n);
void array_free(int **arr);
void find_max_in_rows(int *arr, int **matrix, int m, int n);
void find_min_in_cols(int *arr, int **matrix, int m, int n);
void static_find_max_in_rows(int *arr, int matrix[MAXN][MAXN], int m, int n);
void static_find_min_in_cols(int *arr, int matrix[MAXN][MAXN], int m, int n);
void array_output(int *arr, int n);

int main(void) {
    int rc = OK;
    int mode;
    int m, n;
    int **mat = NULL;
    int static_mat[MAXN][MAXN];
    int *arr_min = NULL, *arr_max = NULL;

    if (scanf("%d", &mode) != 1) rc = ERR_IO;
    if (!rc && (mode <= 0 || mode > 4)) rc = ERR_RANGE;
    if (!rc && scanf("%d%d", &m, &n) != 2) rc = ERR_IO;
    if (!rc && ((n <= 0 || m <= 0))) rc = ERR_RANGE;
    if (!rc && mode == 1 && (n > MAXN || m > MAXN)) rc = ERR_RANGE;
    if (!rc) rc = array_allocate(&arr_min, m);
    if (!rc) rc = array_allocate(&arr_max, n);

    if (!rc) {
        if (mode == 2)
            rc = matrix_allocate_2(&mat, m, n);
        else if (mode == 3)
            rc = matrix_allocate_3(&mat, m, n);
        else if (mode == 4)
            rc = matrix_allocate_4(&mat, m, n);
    }
    if (!rc) {
        if (mode != 1)
            rc = matrix_input(mat, m, n);
        else {
            rc = static_matrix_input(static_mat, m, n);
        }
    }
    if (!rc) {
        if (mode != 1) {
            find_max_in_rows(arr_max, mat, m, n);
            find_min_in_cols(arr_min, mat, m, n);
        } else {
            static_find_max_in_rows(arr_max, static_mat, m, n);
            static_find_min_in_cols(arr_min, static_mat, m, n);
        }
        if (mode != 1) {
            matrix_output((const int **)mat, m, n);
        } else {
            static_matrix_output(&static_mat[0], m, n);
        }
        printf("\n");
        array_output(arr_max, n);
        printf("\n");
        array_output(arr_min, m);
    }
    if (mode == 2)
        matrix_free_2(&mat, m, n);
    else if (mode == 3)
        matrix_free_3(&mat, m, n);
    else if (mode == 4)
        matrix_free_4(&mat, m, n);
    array_free(&arr_max);
    array_free(&arr_min);
    if (rc) printf("n/a");
    return rc;
}

int matrix_allocate_2(int ***matrix, int m, int n) {
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
        matrix_free_2(&single_array_matrix, m, n);
    return rc;
}

void matrix_free_2(int ***matrix, int m, int n) {
    (void)n;
    (void)m;
    if (*matrix) {
        free(*matrix);
        *matrix = NULL;
    }
}

int matrix_allocate_3(int ***matrix, int m, int n) {
    int rc = OK;
    int **pointer_array = malloc(m * sizeof(int *));
    if (!pointer_array) rc = ERR_MEM;
    for (int i = 0; !rc && i < m; i++) {
        pointer_array[i] = malloc(n * sizeof(int));
        if (!pointer_array[i]) rc = ERR_MEM;
    }
    if (rc)
        matrix_free_3(matrix, m, n);
    else
        *matrix = pointer_array;
    return rc;
}

void matrix_free_3(int ***matrix, int m, int n) {
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

int matrix_allocate_4(int ***matrix, int m, int n) {
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
        matrix_free_4(matrix, m, n);
    else
        *matrix = pointer_array;
    return rc;
}

void matrix_free_4(int ***matrix, int m, int n) {
    (void)m;
    (void)n;
    if (*matrix && (*matrix)[0]) free((*matrix)[0]);
    if (*matrix) free(*matrix);
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

int static_matrix_input(int matrix[MAXN][MAXN], int m, int n) {
    int rc = OK;
    for (int i = 0; !rc && i < m; i++) {
        for (int j = 0; !rc && j < n; j++) {
            if (scanf("%d", &matrix[i][j]) != 1) rc = ERR_IO;
        }
    }
    return rc;
}
void static_matrix_output(int matrix[MAXN][MAXN], int m, int n) {
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

int array_allocate(int **arr, int n) {
    int rc = OK;
    int *tmp_arr = malloc(n * sizeof(int));
    if (!tmp_arr)
        rc = ERR_MEM;
    else
        *arr = tmp_arr;
    return rc;
}

void array_free(int **arr) {
    if (*arr != NULL) {
        free(*arr);
        *arr = NULL;
    }
}
void find_max_in_rows(int *arr, int **matrix, int m, int n) {
    for (int i = 0; i < m; i++) {
        int max = matrix[i][0];
        for (int j = 0; j < n; j++) {
            if (matrix[i][j] > max) max = matrix[i][j];
        }
        arr[i] = max;
    }
}

void find_min_in_cols(int *arr, int **matrix, int m, int n) {
    for (int j = 0; j < n; j++) {
        int min = matrix[0][j];
        for (int i = 0; i < m; i++) {
            if (matrix[i][j] < min) min = matrix[i][j];
        }
        arr[j] = min;
    }
}

void static_find_max_in_rows(int *arr, int matrix[MAXN][MAXN], int m, int n) {
    for (int i = 0; i < m; i++) {
        int max = matrix[i][0];
        for (int j = 0; j < n; j++) {
            if (matrix[i][j] > max) max = matrix[i][j];
        }
        arr[i] = max;
    }
}

void static_find_min_in_cols(int *arr, int matrix[MAXN][MAXN], int m, int n) {
    for (int j = 0; j < n; j++) {
        int min = matrix[0][j];
        for (int i = 0; i < m; i++) {
            if (matrix[i][j] < min) min = matrix[i][j];
        }
        arr[j] = min;
    }
}

void array_output(int *arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        printf("%d ", arr[i]);
    }
    printf("%d", arr[n - 1]);
}
