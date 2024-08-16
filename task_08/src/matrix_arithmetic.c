#include <stdio.h>
#include <stdlib.h>

#define OK 0
#define ERR_IO 1
#define ERR_RANGE 2
#define ERR_MEM 3

#define MAXN 100

int matrix_allocate(int ***matrix, int m_1, int n_1);
void matrix_free(int ***matrix, int m_1, int n_1);

int matrix_input(int **matrix, int m_1, int n_1);
void matrix_output(const int **matrix, int m_1, int n_1);

int matrix_summ(const int **mat_1, int m_1, int n_1, const int **mat_2, int m_2, int n_2, int ***mat_r,
                int *m_r, int *n_r);
int matrix_mul(const int **mat_1, int m_1, int n_1, const int **mat_2, int m_2, int n_2, int ***mat_r,
               int *m_r, int *n_r);
int matrix_transpose(const int **mat_1, int m_1, int n_1, int ***mat_r, int *m_r, int *n_r);

int main(void) {
    int rc = OK;
    int mode;
    int m_1 = 0, n_1 = 0;
    int **mat_1 = NULL;
    int m_2 = 0, n_2 = 0;
    int **mat_2 = NULL;

    int m_r = 0, n_r = 0;
    int **mat_r = NULL;

    if (scanf("%d", &mode) != 1) rc = ERR_IO;
    if (!rc && (mode <= 0 || mode > 3)) rc = ERR_RANGE;

    if (!rc && scanf("%d%d", &m_1, &n_1) != 2) rc = ERR_IO;
    if (!rc && ((n_1 <= 0 || m_1 <= 0))) rc = ERR_RANGE;
    if (!rc) {
        rc = matrix_allocate(&mat_1, m_1, n_1);
    }
    if (!rc) {
        rc = matrix_input(mat_1, m_1, n_1);
    }

    if (!rc && mode != 3 && scanf("%d%d", &m_2, &n_2) != 2) rc = ERR_IO;
    if (!rc && mode != 3 && ((n_2 <= 0 || m_2 <= 0))) rc = ERR_RANGE;
    if (!rc && mode != 3) {
        rc = matrix_allocate(&mat_2, m_2, n_2);
    }
    if (!rc && mode != 3) {
        rc = matrix_input(mat_2, m_2, n_2);
    }

    if (!rc) {
        if (mode == 1) {
            rc =
                matrix_summ((const int **)mat_1, m_1, n_1, (const int **)mat_2, m_2, n_2, &mat_r, &m_r, &n_r);
        } else if (mode == 2) {
            rc = matrix_mul((const int **)mat_1, m_1, n_1, (const int **)mat_2, m_2, n_2, &mat_r, &m_r, &n_r);
        } else if (mode == 3) {
            rc = matrix_transpose((const int **)mat_1, m_1, n_1, &mat_r, &m_r, &n_r);
        }
    }
    if (!rc) matrix_output((const int **)mat_r, m_r, n_r);
    matrix_free(&mat_1, m_1, n_1);
    matrix_free(&mat_2, m_2, n_2);
    matrix_free(&mat_r, m_r, n_r);
    if (rc) printf("n/a");
    return rc;
}

int matrix_allocate(int ***matrix, int m_1, int n_1) {
    int rc = OK;
    int **pointer_array = malloc(m_1 * sizeof(int *));
    if (!pointer_array) rc = ERR_MEM;
    for (int i = 0; !rc && i < m_1; i++) {
        pointer_array[i] = malloc(n_1 * sizeof(int));
        if (!pointer_array[i]) rc = ERR_MEM;
    }
    if (rc)
        matrix_free(&pointer_array, m_1, n_1);
    else
        *matrix = pointer_array;
    return rc;
}

void matrix_free(int ***matrix, int m_1, int n_1) {
    (void)n_1;
    if (*matrix != NULL) {
        for (int i = 0; i < m_1; i++) {
            if ((*matrix)[i]) {
                free((*matrix)[i]);
                (*matrix)[i] = 0;
            }
        }
        free(*matrix);
        *matrix = 0;
    }
}

void matrix_output(const int **matrix, int m_1, int n_1) {
    for (int i = 0; i < m_1 - 1; i++) {
        for (int j = 0; j < n_1 - 1; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("%d\n", matrix[i][n_1 - 1]);
    }
    for (int j = 0; j < n_1 - 1; j++) {
        printf("%d ", matrix[m_1 - 1][j]);
    }
    printf("%d", matrix[m_1 - 1][n_1 - 1]);
}

int matrix_input(int **matrix, int m_1, int n_1) {
    int rc = OK;
    for (int i = 0; !rc && i < m_1; i++) {
        for (int j = 0; !rc && j < n_1; j++) {
            if (scanf("%d", &matrix[i][j]) != 1) rc = ERR_IO;
        }
    }
    return rc;
}

int matrix_summ(const int **mat_1, int m_1, int n_1, const int **mat_2, int m_2, int n_2, int ***mat_r,
                int *m_r, int *n_r) {
    int rc = OK;
    if ((m_1 != m_2) || (n_1 != n_2)) {
        rc = ERR_RANGE;
    }
    if (!rc) rc = matrix_allocate(mat_r, m_1, n_1);
    if (!rc) {
        *m_r = m_1;
        *n_r = n_1;
        for (int i = 0; i < m_1; i++) {
            for (int j = 0; j < n_1; j++) {
                (*mat_r)[i][j] = mat_1[i][j] + mat_2[i][j];
            }
        }
    }
    if (rc) matrix_free(mat_r, n_1, m_1);
    return rc;
}

int matrix_mul(const int **mat_1, int m_1, int n_1, const int **mat_2, int m_2, int n_2, int ***mat_r,
               int *m_r, int *n_r) {
    int rc = OK;
    if (n_1 != m_2) {
        rc = ERR_RANGE;
    }
    if (!rc) rc = matrix_allocate(mat_r, m_1, n_2);
    if (!rc) {
        *m_r = m_1;
        *n_r = n_2;

        for (int i = 0; i < m_1; i++) {
            for (int j = 0; j < n_2; j++) {
                (*mat_r)[i][j] = 0;
                for (int k = 0; k < n_1; k++) {
                    (*mat_r)[i][j] += mat_1[i][k] * mat_2[k][j];
                }
            }
        }
    }
    if (rc) matrix_free(mat_r, m_1, n_2);
    return rc;
}

int matrix_transpose(const int **mat_1, int m_1, int n_1, int ***mat_r, int *m_r, int *n_r) {
    int rc = matrix_allocate(mat_r, n_1, m_1);
    if (!rc) {
        *m_r = n_1;
        *n_r = m_1;
        for (int i = 0; i < m_1; i++) {
            for (int j = 0; j < n_1; j++) {
                (*mat_r)[j][i] = mat_1[i][j];
            }
        }
    } else {
        matrix_free(mat_r, n_1, m_1);
    }
    return rc;
}