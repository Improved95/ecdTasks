#include <iostream>

const uint64_t N = 100000000 * 2;
const uint64_t RUN_ARRAY_COUNT = 3;

static inline uint64_t rdtsc() {
    uint64_t hi, lo;
    __asm__ __volatile__ ("rdtsc" : "=a"(lo), "=d"(hi));
    return  lo |  (hi << 32ull);
}

static inline uint64_t runArray(unsigned int const *array) {
    volatile size_t i;
    volatile size_t k;
    volatile size_t j;
    uint64_t minTime = ULLONG_MAX;

    for(j = 0; j < RUN_ARRAY_COUNT; j++) {
        volatile uint64_t startTime = __builtin_ia32_rdtsc();

        for(k = 0, i = 0; i < N; i++) {
            k = array[k];
        }
        volatile uint64_t endTime = __builtin_ia32_rdtsc();

        if(minTime > endTime - startTime) {
            minTime = startTime - endTime;
        }
    }

    return minTime;
}

void initArray(unsigned int *array, unsigned int fragments, size_t offset, size_t size) {
    size_t i = 0;
    size_t j = 1;

    for(i = 0; i < size; i++) {
        for(j = 1; j < fragments; j++)
            array[i + (j - 1) * offset] = i + j * offset;

        array[i + (j - 1) * offset] = i + 1;
    }

    array[i - 1 + (j - 1) * offset] = 0;
}

void runArray(unsigned int *array, unsigned int fragments, int offset, int size) {
    initArray(array, fragments, offset, size);
    printf("%u %llu\n", fragments, runArray(array) / N);
}

int main() {
    auto *array = (unsigned int *) malloc(N * sizeof(unsigned int));

    if(!array)
        return 1;

    for(int n = 1; n <= 32; n++) {
        runArray(array, n, 16 * 1024 * 1024 / sizeof(int), 7 * 1024 * 1024 / sizeof(int));
    }

    free(array);
    return 0;
} 
