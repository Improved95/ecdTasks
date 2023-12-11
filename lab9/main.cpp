#include <iostream>
using namespace std;

#define NUMBER_OF_BYPASS 5
static const size_t N = 100000000 * 2;

uint64_t bypassArray(int const *array, size_t arraySize) {
    uint64_t minTime = ULLONG_MAX;

    for(size_t j = 0; j < NUMBER_OF_BYPASS; j++) {
        volatile uint64_t startTime = __builtin_ia32_rdtsc();

        for(size_t k = 0, i = 0; i < N; i++) {
            k = array[k];
        }
        volatile uint64_t endTime = __builtin_ia32_rdtsc();

        if(minTime > endTime - startTime) {
            minTime = endTime - startTime;
        }
    }

    return minTime;
}

void fillArray(int *array, int fragments, size_t offset, size_t size) {
    size_t i = 0;
    size_t j = 1;

    for(; i < size; i++) {
        for(; j < fragments; j++)
            array[i + (j - 1) * offset] = i + j * offset;

        array[i + (j - 1) * offset] = i + 1;
    }

    array[i - 1 + (j - 1) * offset] = 0;
}

void runArray(int *array, int fragments, int offset, int arraySize) {
    fillArray(array, fragments, offset, arraySize);
    printf("%u %llu\n", fragments, bypassArray(array, arraySize) / N);
}

int main() {
    // const size_t arraySize = 17 * 1024 * 1024 / sizeof(int);

    auto *array = (int*) malloc(N * sizeof(int));

    if(!array) { return 1; }
        
    for(int n = 1; n <= 32; n++) {
        runArray(array, n, 16 * 1024 * 1024 / sizeof(int), 17 * 1024 * 1024 / sizeof(int));
    }

    free(array);
    return 0;
} 
