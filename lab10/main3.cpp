#include <iostream>
#include <time.h>
#include <limits.h>
#include <fstream>
#include <cstring>
using namespace std;

// версия с обходом саттолло + шаг

void sattoloFill(int *a, size_t len) {
    memset(a, 0, len);
    int i, j;
    srand(unsigned(time(0)));
    for (size_t k = 0; k < len; k++) {
        a[k] = k;
    }
    for(i = len - 1; i > 0; i--) {
        do {
            j = rand() % i;
        } while(j >= i);
        std::swap(a[i], a[j]);
    }
}

void trashCache(int *arr, size_t len) {
    int k = 0;
    for (size_t i = 0; i < len; i++) {
        k = arr[k];
    }
    cerr << k;
}

size_t bypass(int *arr, int step, size_t len) {
    int k = 0, sk = 0, bypassNumber = 5;
    volatile size_t startTime, endTime;

    startTime = __builtin_ia32_rdtsc();
    for (int j = 0; j < bypassNumber; ++j) {
        for (size_t i = 0; i < len; ++i) {
            sk = arr[k];
            k = arr[sk + step];
        }
    }
    endTime = __builtin_ia32_rdtsc();
    
    cerr << k + sk;

    return (endTime - startTime) / bypassNumber;
}

int main() {
    ofstream fileOut;
    fileOut.open("time.txt");

    size_t trashArrSize = 14 * 1024 * 1024 / sizeof(int);
    int *trashArr = new int[trashArrSize];
    sattoloFill(trashArr, trashArrSize);

    int arrSize = 50 * 1024 * 1024 / sizeof(int);
    int *arr = new int[arrSize];
    sattoloFill(arr, arrSize - 40);

    for (size_t step = 0; step < 32; ++step) {
        fileOut << step * sizeof(int) << " " << bypass(arr, step, arrSize) << endl;;
    }

    delete[] trashArr;
    delete[] arr;
    return 0;
}