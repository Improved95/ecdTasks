#include <iostream>
#include <time.h>
#include <limits.h>
#include <fstream>
#include <cstring>
using namespace std;

static const size_t BYTE_NUM = 1024;
static const size_t MAIN_STEP = 30 * 1024 / sizeof(size_t);

void fillArray(size_t *arr, size_t arrSize, size_t step) {
    for (size_t i = 0; i < arrSize; i++) {
        arr[i] = 0;
    }
    
    size_t index = 0;
    for (size_t i = 1; i < MAIN_STEP; i++) {
        arr[index] = index + step;
        size_t newIndex = ((i * MAIN_STEP) + (rand() % MAIN_STEP)) % arrSize;
        arr[index + step] = newIndex;
        index = newIndex;
    }
}

size_t bypass(size_t *arr, size_t arrSize) {
    size_t k = 0, res = 0, bypassNumber = 400;

    volatile size_t startTime = __builtin_ia32_rdtsc();
    for (size_t j = 0; j < bypassNumber; j++) {
        for (size_t i = 0; i < arrSize / MAIN_STEP; ++i) {
            k = arr[k];
            k = arr[k];
        }
        res += k;
        k = 0;
    }
    volatile size_t endTime = __builtin_ia32_rdtsc();

    cerr << res;

    return (endTime - startTime) / ((arrSize / MAIN_STEP) * bypassNumber);
}

int main() {
    ofstream fileOut;
    fileOut.open("time.txt");

    const size_t arrSize = BYTE_NUM * 1024 * 1024 / sizeof(size_t); 
    size_t *arr = new size_t[arrSize];

    for (size_t step = 1; step < 150; ++step) {
        fillArray(arr, arrSize, step);
        fileOut << step << " " << bypass(arr, arrSize) << endl;
    }
    
    delete[] arr;
    return 0;
}