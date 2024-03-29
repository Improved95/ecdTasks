#include <iostream>
#include <time.h>
#include <limits.h>
#include <fstream>
#include <cstring>
using namespace std;

static const size_t BYTE_NUM = 1024;
static const size_t MAIN_STEP = 2560;

void fillArray(unsigned int *arr, size_t arrSize, size_t step) {
    for (size_t i = 0; i < arrSize; i++) {
        arr[i] = 0;
    }
    
    unsigned int index = 0;
    for (size_t i = 1; i < MAIN_STEP; i++) {
        arr[index] = index + step;
        unsigned int newIndex = (i * MAIN_STEP) + (rand() % MAIN_STEP);
        arr[index + step] = newIndex;
        index = newIndex;
    }
}

size_t bypass(unsigned int *arr, size_t arrSize) {
    unsigned int k = 0, res = 0;

    volatile size_t startTime = __builtin_ia32_rdtsc();
    for (size_t j = 0; j < 200; j++) {
        for (size_t i = 0; i < arrSize / (MAIN_STEP); ++i) {
            k = arr[k];
            k = arr[k];
        }
        res += k;
        k = 0;
    }
    volatile size_t endTime = __builtin_ia32_rdtsc();

    cerr << res;

    return (endTime - startTime) / (arrSize / (MAIN_STEP)) / 200;
}

int main() {
    ofstream fileOut;
    fileOut.open("time.txt");

    const size_t arrSize = BYTE_NUM * 1024 * 1024 / sizeof(unsigned int); 
    unsigned int *arr = new unsigned int[arrSize];

    for (size_t step = 1; step < 200; ++step) {
        fillArray(arr, arrSize, step);
        fileOut << step << " " << bypass(arr, arrSize) << endl;
    }
    
    delete[] arr;
    return 0;
}