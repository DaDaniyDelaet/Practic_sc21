/*------------------------------------
        Здравствуй, человек!
        Чтобы получить ключ
        поработай с комментариями.
-------------------------------------*/

#include <stdio.h>
#define NMAX 10

#define OK 0
#define ERR_IO 1
#define ERR_RANGE 2

int input(int *buffer, int *length);
void output(int *buffer, int length);
int sum_numbers(int const *buffer, int length);
int find_numbers(int *buffer, int length, int number, int *numbers);

/*------------------------------------
        Функция получает массив данных
        через stdin.
        Выдает в stdout особую сумму
        и сформированный массив
        специальных элементов
        (выбранных с помощью найденной суммы):
        это и будет частью ключа
-------------------------------------*/
int main() {
    int n, nums[NMAX];
    int rc = input(nums, &n);
    if (!rc) {
        int sum = sum_numbers(nums, n);
        printf("%d\n", sum);
        int ans[NMAX];
        int ans_len = find_numbers(nums, n, sum, ans);
        if (ans_len > 0)
            output(ans, ans_len);
        else
            printf("n/a");
    } else {
        printf("n/a");
    }
    return rc;
}

int input(int *a, int *n) {
    int rc = OK;
    if (scanf("%d", n) != 1) rc = ERR_IO;
    if (!rc && (*n <= 0 || *n > NMAX)) rc = ERR_RANGE;
    for (int *p = a; !rc && p - a < *n; p++) {
        if (scanf("%d", p) != 1) rc = ERR_IO;
    }
    return rc;
}

void output(int *a, int n) {
    for (int *x = a; x < a + n; x++) {
        printf("%d", *x);
        if (x < a + n - 1) printf(" ");
    }
}

/*------------------------------------
        Функция должна находить
        сумму четных элементов
        с 0-й позиции.
-------------------------------------*/
int sum_numbers(int const *buffer, int length) {
    int sum = 0;

    for (int i = 0; i < length; i++) {
        if (buffer[i] % 2 == 0) {
            sum = sum + buffer[i];
        }
    }

    return sum;
}

/*------------------------------------
        Функция должна находить
        все элементы, на которые нацело
        делится переданное число и
        записывает их в выходной массив.
-------------------------------------*/
int find_numbers(int *buffer, int length, int number, int *numbers) {
    int numbers_len = 0;
    for (int *bx = buffer; bx < buffer + length; ++bx) {
        if (*bx != 0 && number % (*bx) == 0) {
            numbers[numbers_len++] = *bx;
        }
    }
    return numbers_len;
}
