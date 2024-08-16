#include <stdio.h>

#define LEN 100
#define OK 0
#define ERR_IO 1
#define ERR_RANGE 2

int input(int *buffer, int *length);
void output(int *buffer, int length);
void sum(int const *buff1, int len1, int const *buff2, int len2, int *result, int *result_length);
void sub(int const *buff1, int len1, int const *buff2, int len2, int *result, int *result_length);

/*
    Беззнаковая целочисленная длинная арифметика
    с использованием массивов.
    Ввод:
     * 2 длинных числа в виде массивов до 100 элементов
     * В один элемент массива нельзя вводить число > 9
    Вывод:
     * Результат сложения и разности чисел-массивов
    Пример:
     * 1 9 4 4 6 7 4 4 0 7 3 7 0 9 5 5 1 6 1
       2 9

       1 9 4 4 6 7 4 4 0 7 3 7 0 9 5 5 1 9 0
       1 9 4 4 6 7 4 4 0 7 3 7 0 9 5 5 1 3 2
*/
int main() {
    int n_1, arr_1[LEN];
    int n_2, arr_2[LEN];

    int rc = input(arr_1, &n_1);
    if (!rc) rc = input(arr_2, &n_2);
    if (!rc) {
        int n_3, arr_3[LEN];
        sum(arr_1, n_1, arr_2, n_2, arr_3, &n_3);
        output(arr_3, n_3);
        printf("\n");
        sub(arr_1, n_1, arr_2, n_2, arr_3, &n_3);
        output(arr_3, n_3);
    }
    if (rc) printf("n/a");
    return rc;
}

int input(int *a, int *n) {
    *n = 0;
    for (int *p = a; p - a < LEN; p++) {
        if (scanf("%d", p) != 1) return ERR_IO;
        (*n)++;
        if (getchar() == '\n') return OK;
    }
    return ERR_IO;
}

void output(int *a, int n) {
    if (n == 0) printf("n/a");
    for (int *x = a; x < a + n; x++) {
        printf("%d", *x);
        if (x < a + n - 1) printf(" ");
    }
}

void swap(int *xp, int *yp) {
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void reverse(int *buf, int len) {
    for (int i = 0; i < len / 2; i++) {
        swap(&buf[i], &buf[len - i - 1]);
    }
}

void sum(int const *buff1, int len1, int const *buff2, int len2, int *result, int *result_length) {
    int digit_summ;
    int shifted = 0;
    *result_length = 0;
    int i = len1 - 1, j = len2 - 1;
    for (; i >= 0 && j >= 0 && *result_length < LEN; i--, j--) {
        digit_summ = buff1[i] + buff2[j] + shifted;
        result[(*result_length)++] = digit_summ % 10;
        shifted = digit_summ / 10;
    }
    for (; i >= 0 && *result_length < LEN; i--) {
        digit_summ = buff1[i] + shifted;
        result[(*result_length)++] = digit_summ % 10;
        shifted = digit_summ / 10;
    }
    for (; j >= 0 && *result_length < LEN; j--) {
        digit_summ = buff2[j] + shifted;
        result[(*result_length)++] = digit_summ % 10;
        shifted = digit_summ / 10;
    }
    if (shifted != 0 && *result_length < LEN) {
        result[(*result_length)++] = shifted;
    }
    if (*result_length >= LEN) *result_length = 0;
    for (; *result_length > 0 && result[*result_length - 1] == 0; (*result_length)--)
        ;
    reverse(result, *result_length);
}

void sub(int const *buff1, int len1, int const *buff2, int len2, int *result, int *result_length) {
    int digit_summ;
    int shifted = 0;
    *result_length = 0;
    int i = len1 - 1, j = len2 - 1;
    for (; i >= 0 && j >= 0; i--, j--) {
        digit_summ = buff1[i] - buff2[j] + shifted;
        if (digit_summ % 10 >= 0)
            result[(*result_length)++] = digit_summ % 10;
        else
            result[(*result_length)++] = 10 + digit_summ % 10;
        if (digit_summ < 0)
            shifted = -1;
        else
            shifted = digit_summ / 10;
    }
    for (; i >= 0; i--) {
        digit_summ = buff1[i] + shifted;
        result[(*result_length)++] = digit_summ % 10;
        shifted = digit_summ / 10;
    }
    if (shifted != 0 || j >= 0) {
        *result_length = 0;
    }
    for (; *result_length > 0 && result[*result_length - 1] == 0; (*result_length)--)
        ;
    reverse(result, *result_length);
}
