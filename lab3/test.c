#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b) {
    int c = *a;
    *a = *b;
    *b = c;
}

int main(int argc, char *argv[]) {
    int a = argc;
    char* b = argv[1];
    int c = *b - '\0';

    printf("%d", c);

    return 0;
}