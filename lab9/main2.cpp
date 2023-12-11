#include <iostream>
#include <fstream>
using namespace std;

const size_t N = 100000000 * 2;
#define NUMBER_OF_BYPASS 5

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

void initArray(unsigned int *array, unsigned int fragments, size_t offset, size_t size)
{
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

void runArray(unsigned int *array, unsigned int fragments, int offset, int size) {
    initArray(array, fragments, offset, size);
    printf("%u\t %llu\n", fragments, bypassArray(array) / N);
}

int main() {
    ofstream fileOut;
    fileOut.open("time.txt");
    auto *array = (unsigned int *) malloc(N * sizeof(unsigned int));

    if(!array) { return 1; }

    for(int n = 1; n <= 32; n++) {
        runArray(array, n, 16 * 1024 * 1024 / sizeof(int), 17 * 1024 * 1024 / sizeof(int));
    }

    free(array);
    return 0;
} 
