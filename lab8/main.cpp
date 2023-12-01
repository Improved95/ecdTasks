#include <iostream>
#include <x86intrin.h>
#include <limits.h>
using namespace std;

void sattoloFill(size_t *a, size_t len) {
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

void forwardFill(size_t *arr, size_t len) {
    for (size_t i = 0; i < len - 1; i++) {
        arr[i] = i + 1;
    }
    arr[len - 1] = 0;
}

void backwardFill(size_t *arr, size_t len) {
    arr[0] = len - 1;
    for (size_t i = 1; i < len; i++) {
        arr[i] = i - 1;
    }
}

void warmingUpMemory(size_t *arr, size_t len) {
    size_t k = 0;
    for (size_t i = 0; i < 10; i++) {
        for (size_t j = 0; j < len; j++) {
            k = arr[k];
        }
    }
}

uint64_t bypass(size_t *arr, size_t len) {
    warmingUpMemory(arr, len);

    uint64_t averageTime = 0;
    size_t k = 0;
    for (size_t i = 0; i < 10; i++) {
        for (size_t j = 0; j < len; j++) {
            uint64_t startTime = __rdtsc();
            k = arr[k];
            uint64_t endTime = __rdtsc();
            averageTime = (averageTime*(i + 1) + (endTime - startTime)) / (i + 2);
            // cout << endTime << " " << startTime << endl;
        }
    }
    
            
            // exit(EXIT_FAILURE);

    // return endTime - startTime;
    return averageTime;
}

void fillAndBypass(void(*fillType)(size_t *arr, size_t len)) {
    const size_t n_min = 1 * 1024 / sizeof(size_t); //1kb
    const size_t n_max = 32 * 1024 * 1024 / sizeof(size_t); //32mb
    size_t step = 8 * 1024 / sizeof(size_t); //8kb

    bool sf1 = true, sf2 = true, sf3 = true;
    uint64_t minTimeMemoryCalls = ULLONG_MAX;

    for (size_t i = n_min; i < n_max; i += step) {
        size_t *arr = new size_t[i];
        if (!arr) { cout << "er" << endl; exit(EXIT_FAILURE); }

        fillType(arr, i);
        for (size_t j = 0; j < 5; j++) {
            auto averageTimeMemoryCalls = bypass(arr, i);
            if (averageTimeMemoryCalls < minTimeMemoryCalls) {
                minTimeMemoryCalls = averageTimeMemoryCalls;
            }
        }

        cout << i * sizeof(size_t) / 1024 << "kb " << minTimeMemoryCalls << " " << endl;

        if (sf1 && i * sizeof(size_t) > 256 * 1024) { // more then 256kb
            // cout << "go in 64kb" << endl; 
            step = 64 * 1024 / sizeof(size_t);
            sf1 = false;
        }
        if (sf3 && i * sizeof(size_t) > 2 * 1024 * 1024) { // more then 2mb
            // cout << "go in 2mb" << endl; 
            step = 2 * 1024 * 1024 / sizeof(size_t);
            sf3 = false;
        }

        delete[] arr;
    }
}

int main() {

    cout << "forward bypass" << endl;
    fillAndBypass(forwardFill);

    cout << endl << "backward bypass" << endl;
    fillAndBypass(backwardFill);

    cout << endl << "random bypass" << endl;
    fillAndBypass(sattoloFill);

    return 0;
}