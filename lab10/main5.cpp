#include <iostream>
#include <time.h>
#include <limits.h>
#include <fstream>
#include <cstring>
using namespace std;

#define BYTE_NUM 256
#define MAIN_STEP 10

void fillArray(unsigned int *arr, size_t arrSize, size_t step) {
    for (size_t i = 0; i < arrSize; i++) {
        arr[i] = 0;
    }
    
    unsigned int index = 0;
    for (size_t i = 1; i < BYTE_NUM * MAIN_STEP; i++) {
        arr[index] = index + step;
        unsigned int newIndex = (i * BYTE_NUM * MAIN_STEP) + (rand() % BYTE_NUM * MAIN_STEP);
        arr[index + step] = newIndex;
        index = newIndex;
    }
}

size_t bypass(unsigned int *arr, size_t arrSize) {
    unsigned int k = 0;

    volatile size_t startTime = __builtin_ia32_rdtsc();
    for (size_t j = 0; j < 20; j++) {
        for (size_t i = 0; i < arrSize / (BYTE_NUM * MAIN_STEP); ++i) {
            k = arr[k];
            k = arr[k];
        }
    }
    volatile size_t endTime = __builtin_ia32_rdtsc();

    return (endTime - startTime) / (arrSize / (BYTE_NUM * MAIN_STEP)) / 20;
}

int main() {
    ofstream fileOut;
    fileOut.open("time.txt");

    const size_t arrSize = BYTE_NUM * 1024 * 1024 / sizeof(unsigned int); 
    // const size_t arrSize = 1024 / sizeof(unsigned int); 
    unsigned int *arr = new unsigned int[arrSize]; // 256mb

    for (size_t step = 1; step < 70; ++step) {
        fillArray(arr, arrSize, step);
        fileOut << step << " " << bypass(arr, arrSize) << endl;
    }
    
    delete[] arr;
    return 0;
}