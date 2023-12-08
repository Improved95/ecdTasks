#include <iostream>
#include <time.h>
#include <limits.h>
#include <fstream>
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
    for (size_t j = 0; j < len; j++) {
        k = arr[k];
    }
}

size_t bypass(size_t *arr, size_t len) {
    warmingUpMemory(arr, len);
    
    size_t k = 0;
    volatile size_t startTime = __builtin_ia32_rdtsc();
    for (size_t i = 0; i < 10; i++) {
        for (size_t j = 0; j < len; j++) {
            k = arr[k];
        }
    }
    volatile size_t endTime = __builtin_ia32_rdtsc();
    cerr << k;

    return (endTime - startTime) / (10 * len);
}

void fillAndBypass(void(*fillType)(size_t *arr, size_t len), ofstream &fileOut) {
    const size_t n_min = 1 * 1024 / sizeof(size_t); //1kb
    const size_t n_max = 32 * 1024 * 1024 / sizeof(size_t); //32mb
    size_t step = 16 * 1024 / sizeof(size_t); //8kb

    bool sf1 = true;
    bool sf2 = true;
    size_t timeMemoryCalls = 0, minTimeMemoryCalls = ULLONG_MAX;

    for (size_t i = n_min; i < n_max; i += step) {
        size_t *arr = new size_t[i];
        if (!arr) { cout << "er" << endl; exit(EXIT_FAILURE); }

        fillType(arr, i);
        for (size_t j = 0; j < 5; j++) {
            timeMemoryCalls = bypass(arr, i);
            if (timeMemoryCalls < minTimeMemoryCalls) {
                minTimeMemoryCalls = timeMemoryCalls;
            }
        }

        fileOut << i * sizeof(size_t) / 1024 << " " << timeMemoryCalls << " " << endl;

        if (sf1 && i * sizeof(size_t) > 256 * 1024) { // more then 256kb
            step = 32 * 1024 / sizeof(size_t);
            sf1 = false;
        }
        if (sf2 && i * sizeof(size_t) > 2 * 1024 * 1024) { // more then 2mb
            step = 512 * 1024 / sizeof(size_t);
            sf2 = false;
        }

        delete[] arr;
    }
}

int main() {
    ofstream fileOut;
    fileOut.open("time.txt");

    fileOut << "forward bypass" << endl;
    fillAndBypass(forwardFill, fileOut);

    fileOut << endl << "backward bypass" << endl;
    fillAndBypass(backwardFill, fileOut);

    fileOut << endl << "random bypass" << endl;
    fillAndBypass(sattoloFill, fileOut);

    return 0;
}