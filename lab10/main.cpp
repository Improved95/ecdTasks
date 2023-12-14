#include <iostream>
#include <time.h>
#include <limits.h>
#include <fstream>
using namespace std;

void sattoloFill(int *a, size_t len) {
    int i, j;
    srand(unsigned(time(0)));
    for (size_t k = 0; k < len; k++) {
        a[k] = k;
    }
    for(i = len - 1; i > 0; i--) {
        do {
            j = rand() % i;
        } while(j >= i);
        swap(a[i], a[j]);
    }
}    

size_t bypass(int *arr, size_t step, size_t len) {
    
    size_t k = 0, sk = 0;
    volatile size_t time = 0;
    for (size_t i = 0; i < len; i++) {
        sk = arr[k];
        volatile size_t startTime = __builtin_ia32_rdtsc();
        k = arr[sk + step];
        volatile size_t endTime = __builtin_ia32_rdtsc();

        time += endTime - startTime;
    }
    cerr << k;
    cerr << sk;

    return time / len;
}

int main() {
    ofstream fileOut;
    fileOut.open("time.txt");

    size_t len = 64 * 1024 * 1024 / sizeof(int);
    int *arr = new int[len * sizeof(int)];

    sattoloFill(arr, len - 128);

    for (size_t i = 10; i < 20; i++) {
        fileOut << i << " " << bypass(arr, i, len) << endl;
    }

}