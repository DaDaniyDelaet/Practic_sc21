#include <stdio.h>
#define NMAX 10

#define OK 0
#define ERR_IO 1
#define ERR_RANGE 2

int input(int *a);
void output(int *a);
void quick_sort(int *a, int low, int hight);
void heap_sort(int *numbers, int array_size);

int main() {
    int data[NMAX];
    int rc = OK;
    rc = input(data);
    if (!rc) {
        int tmp_data[NMAX];
        for (int i = 0; i < NMAX; i++) tmp_data[i] = data[i];
        quick_sort(data, 0, NMAX - 1);
        output(data);
        printf("\n");
        heap_sort(tmp_data, NMAX);
        output(tmp_data);
    } else {
        printf("n/a");
    }

    return rc;
}

int input(int *a) {
    int rc = OK;
    for (int *p = a; !rc && p - a < NMAX; p++) {
        if (scanf("%d", p) != 1) rc = ERR_IO;
    }
    return rc;
}

void output(int *a) {
    for (int *x = a; x < a + NMAX; x++) {
        printf("%d", *x);
        if (x < a + NMAX - 1) printf(" ");
    }
}

void swap(int *xp, int *yp) {
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

int partition(int *arr, int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quick_sort(int *arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);

        quick_sort(arr, low, pi - 1);
        quick_sort(arr, pi + 1, high);
    }
}

void siftDown(int *numbers, int root, int bottom) {
    int maxChild;
    int done = 0;

    while ((root * 2 <= bottom) && (!done)) {
        if (root * 2 == bottom)
            maxChild = root * 2;

        else if (numbers[root * 2] > numbers[root * 2 + 1])
            maxChild = root * 2;
        else
            maxChild = root * 2 + 1;

        if (numbers[root] < numbers[maxChild]) {
            int temp = numbers[root];
            numbers[root] = numbers[maxChild];
            numbers[maxChild] = temp;
            root = maxChild;
        } else
            done = 1;
    }
}

void heap_sort(int *numbers, int array_size) {
    for (int i = (array_size / 2); i >= 0; i--) siftDown(numbers, i, array_size - 1);

    for (int i = array_size - 1; i >= 1; i--) {
        int temp = numbers[0];
        numbers[0] = numbers[i];
        numbers[i] = temp;
        siftDown(numbers, 0, i - 1);
    }
}
