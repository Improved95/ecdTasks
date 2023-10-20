#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b) {
    int c = *a;
    *a = *b;
    *b = c;
}

int main(int argc, char* argv[]) {
    size_t n = atoi(argv[1]);
    int *arr = malloc(n * sizeof(int));

    for (size_t i = 0; i < n; i++) {
        arr[i] = n - i;
    }

    for (size_t i = 0; i < n - 1; i++) {
        for (size_t j = 0; j < n - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(&arr[j], &arr[j + 1]);
            }
        }
    }

    for (size_t i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
}