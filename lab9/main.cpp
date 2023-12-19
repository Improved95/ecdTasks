#include <iostream>
#include <fstream>
using namespace std;

const static size_t N = 17 * 32 * 1024 * 1024 / sizeof(int);
#define NUMBER_OF_BYPASS 20

uint64_t bypassArray(unsigned int const *array) {
    volatile size_t i;
    volatile size_t k;
    uint64_t minTime = ULLONG_MAX;

    for(size_t j = 0; j < NUMBER_OF_BYPASS; j++)
    {
        volatile uint64_t startTime = __builtin_ia32_rdtsc();

        for(k = 0, i = 0; i < N; i++) {
            k = array[k];
        }
        volatile uint64_t endTime = __builtin_ia32_rdtsc();

        if(minTime > endTime - startTime) {
            minTime = endTime - startTime;
        }
    }

    return minTime;
}

void initArray(unsigned int *array, unsigned int fragments, size_t offset, size_t size) {
    size_t i = 0;
    size_t j = 1;

    for(i = 0; i < size; i++) {
        for(j = 1; j < fragments; j++) {
            array[i + (j - 1) * offset] = i + j * offset;
        }
        array[i + (j - 1) * offset] = i + 1;
    }

    array[i - 1 + (j - 1) * offset] = 0;
}

int main() {
    ofstream fileOut;
    fileOut.open("time.txt");
    unsigned int *array = new unsigned int[N * sizeof(unsigned int)];

    if(!array) { return 1; }

    for(int i = 1; i <= 32; i++) {
        initArray(array, i, 16 * 1024 * 1024 / sizeof(int), 17 * 1024 * 1024 / sizeof(int));
        fileOut << i << " " << bypassArray(array) / N << endl;
    }

    delete[] array;
    fileOut.close();
    return 0;
} 
